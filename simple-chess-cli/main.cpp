/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016, 2017, 2018, 2020  Dirk Stolle

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 -------------------------------------------------------------------------------
*/

#include <iostream>
#include "../data/Board.hpp"
#include "../evaluation/CompoundCreator.hpp"
#include "../evaluation/CompoundEvaluator.hpp"
#include "../search/Search.hpp"
#include "../ui/Console.hpp"
#include "../util/GitInfos.hpp"
#include "../util/ReturnCodes.hpp"
#include "../util/Version.hpp"


void showVersion()
{
  simplechess::GitInfos info;
  std::cout << "simple-chess-cli, " << simplechess::version << "\n"
            << "\n"
            << "Version control commit: " << info.commit() << "\n"
            << "Version control date:   " << info.date() << std::endl;
}

void showHelp()
{
  std::cout << "simple-chess-cli [OPTIONS]\n"
            << "\n"
            << "options:\n"
            << "  -? | --help     - shows this help message and exits\n"
            << "  -v | --version  - shows version information and exits\n"
            << "  w | white       - let the engine be the white player\n"
            << "  b | black       - let the engine be the black player\n"
            << "                    (The default is to play none, i.e. both sides are human.)\n"
            << "  FEN             - a valid Forsyth-Edwards notation that indicates the\n"
            << "                    initial position for the chess game. Default is the normal\n"
            << "                    chess start position.\n"
            << "  -e EVAL         - sets a custom set of evaluators to use where EVAL is a\n"
            << "                    comma-separated list of evaluator ids. Valid ids are:\n"
            << "                      material: evaluator using material value of pieces\n"
            << "                      check: evaluator with bonus for checking opponent\n"
            << "                       castling: evaluator with malus for not castling before\n"
            << "                                 the possibility for castling is lost\n"
            << "                      promotion: evaluator with bonus for pawns that can be\n"
            << "                                 promoted during the next move\n"
            << "                      linearmobility: bonus for number of possible moves over\n"
            << "                                      all pieces by a player\n"
            << "                      rootmobility: like linearmobility, but with a slower\n"
            << "                                    increase for higher move numbers\n"
            << "                    A possible use of this option can look like this:\n"
            << "                      --evaluator check,promotion,material\n"
            << "                    If no evaluator option is given, the program uses a preset.\n"
            << "                    Evaluators are used by computer players only, so this\n"
            << "                    has no effect when two humans play against each other.\n";
}

/** \brief Prints a board to the standard output.
 *
 * \param board   the chess board
 */
void showBoard(const simplechess::Board& board)
{
  simplechess::ui::Console::showBoard(board);
  std::cout << "\n";
  if (board.toMove() == simplechess::Colour::white)
    std::cout << "White is to move.\n";
  else
    std::cout << "Black is to move.\n";
}


/** \brief Gets a field from the standard input.
 *
 * \return Returns the field that was entered by the user.
 */
simplechess::Field getField()
{
  std::string input;
  std::cin >> input;
  if (input.size() < 2)
    input = "a1";
  char c = input[0];
  int r = input[1] - '1' + 1;
  return simplechess::toField(c, r);
}


int main(int argc, char** argv)
{
  simplechess::Board board;
  simplechess::Colour computerPlayer = simplechess::Colour::none;
  bool doneFEN = false;
  std::string evaluators = "";

  // Use default start position.
  if (!board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"))
  {
    std::cerr << "Could not initialize board from FEN string!\n";
    return 1;
  }

  if ((argc > 1) && (argv != nullptr))
  {
    for (int i = 1; i < argc; ++i)
    {
      if (argv[i] == nullptr)
      {
        std::cerr << "Error: Parameter at index " << i << " is null pointer!\n";
        return simplechess::rcInvalidParameter;
      }
      const std::string param(argv[i]);
      if ((param == "-v") || (param == "--version"))
      {
        showVersion();
        return 0;
      } // if version
      else if ((param == "-?") || (param == "--help") || (param == "/?"))
      {
        showHelp();
        return 0;
      } // if help
      // Set engine's side.
      else if ((param == "white") || (param == "w"))
      {
        computerPlayer = simplechess::Colour::white;
        std::cout << "Engine will play as white.\n";
      }
      else if ((param == "black") || (param == "b"))
      {
        computerPlayer = simplechess::Colour::black;
        std::cout << "Engine will play as black.\n";
      }
      // custom list of evaluators
      else if ((param == "--evaluators") || (param == "--evaluator") || (param == "-e"))
      {
        if (!evaluators.empty())
        {
          std::cout << "Error: The parameter " << param << " cannot be specified more than once!\n";
          return simplechess::rcInvalidParameter;
        }
        if (argc > i + 1)
        {
          evaluators = std::string(argv[i+1]);
          // Skip next argument, because that was already processed.
          ++i;
        }
        else
        {
          std::cout << "Error: There must be a list of evaluators after " << param << "!\n";
          return simplechess::rcInvalidParameter;
        }
      } // if list of evaluators was given
      else if (!doneFEN && board.fromFEN(param))
      {
        std::cout << "Initialized board from FEN string \"" << param << "\".\n";
        doneFEN = true;
      }
      // Should never happen.
      else
      {
        std::cerr << "Error: Unknown parameter " << param << "!\n"
                  << "Use --help to show available parameters." << std::endl;
        return simplechess::rcInvalidParameter;
      }
    } // for i
  } // if arguments are there

  simplechess::CompoundEvaluator evaluator;
  if (evaluators.empty())
  {
    // Fall back to default evaluator set.
    simplechess::CompoundCreator::getDefault(evaluator);
  }
  else
  {
    // Try to parse user input.
    if (!simplechess::CompoundCreator::create(evaluators, evaluator))
    {
      std::cout << "Error: The given evaluator list is invalid!\n";
      return simplechess::rcInvalidParameter;
    } // if
  } // else

  // potentially endless game loop
  while (true)
  {
    showBoard(board);
    std::cout << "\n";
    if (board.toMove() != computerPlayer)
    {
      std::cout << "Your move starts from field: ";
      const simplechess::Field start = getField();
      std::cout << "Your move goes to field: ";
      const simplechess::Field destination = getField();
      if (!board.move(start, destination, simplechess::PieceType::queen))
      {
        std::cout << "The move is not allowed!\n";
        return 2;
      }
    } // user moves
    else
    {
      // Let's find a suitable move.
      simplechess::Search s(board);
      // Search for best move, only two plies.
      s.search(evaluator, 2);
      // Did the search find any moves?
      if (!s.hasMove())
      {
        std::cout << "simplechess AI could not find a valid move. User wins!\n";
        return 0;
      }
      const auto bestMove = s.bestMove();
      const simplechess::Field from = std::get<0>(bestMove);
      const simplechess::Field to = std::get<1>(bestMove);
      const simplechess::PieceType promo = std::get<2>(bestMove);
      std::cout << "Computer moves from " << simplechess::column(from) << simplechess::row(from)
                << " to " << simplechess::column(to) << simplechess::row(to) << ".\n";
      if (!board.move(from, to, promo))
      {
        std::cout << "The computer move is not allowed! User wins.\n";
        return 2;
      }
    } // computer moves
  } // while

  return 0;
}
