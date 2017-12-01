/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016, 2017  Dirk Stolle

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
#include "../evaluation/CheckEvaluator.hpp"
#include "../evaluation/CompoundEvaluator.hpp"
#include "../evaluation/MaterialEvaluator.hpp"
#include "../evaluation/MobilityEvaluator.hpp"
#include "../evaluation/PromotionEvaluator.hpp"
#include "../search/Search.hpp"
#include "../ui/Console.hpp"


/** \brief prints a board to the standard output
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


/** \brief gets a field from the standard input
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
  if (argv != nullptr)
  {
    if ((argc > 1) && (argv[1] != nullptr))
    {
      const std::string fenString = std::string(argv[1]);
      if (!board.fromFEN(fenString))
      {
        std::cerr << "Could not initialize board from FEN string \"" << fenString
                  << "\"!\n";
        return 1;
      }
    } //if one argument is given
    else
    {
      //use default start position
      if (!board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"))
      {
        std::cerr << "Could not initialize board from FEN string!\n";
        return 1;
      }
    } //else
    if ((argc > 2) && (argv[2] != nullptr))
    {
      const std::string colourString = std::string(argv[2]);
      if ((colourString == "white") || (colourString == "w"))
      {
        computerPlayer = simplechess::Colour::white;
      }
      else if ((colourString == "black") || (colourString == "b"))
      {
        computerPlayer = simplechess::Colour::black;
      }
      else
      {
        std::cerr << "The string \"" << colourString << "\" does not name a valid colour / player!\n";
        return 1;
      } //else (unrecognized colour)
    } // if second argument is given
  } // if arguments are there
  //potentially endless game loop
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
      simplechess::Search s;
      simplechess::CompoundEvaluator evaluator;
      // Add the four evaluators we have so far.
      evaluator.add(std::unique_ptr<simplechess::Evaluator>(new simplechess::MaterialEvaluator()));
      evaluator.add(std::unique_ptr<simplechess::Evaluator>(new simplechess::MobilityEvaluator()));
      evaluator.add(std::unique_ptr<simplechess::Evaluator>(new simplechess::PromotionEvaluator()));
      evaluator.add(std::unique_ptr<simplechess::Evaluator>(new simplechess::CheckEvaluator()));
      // Search for best move, only one ply.
      const auto node = s.search(board, evaluator, 1);
      // Did the search find any moves?
      if (node.children.empty())
      {
        std::cout << "simplechess AI could not find a valid move. User wins!\n";
        return 0;
      }
      simplechess::Field from = simplechess::Field::none;
      simplechess::Field to = simplechess::Field::none;
      if (board.toMove() == simplechess::Colour::black)
      {
        from = node.children.front()->move.origin();
        to = node.children.front()->move.destination();
      }
      else
      {
        from = node.children.back()->move.origin();
        to = node.children.back()->move.destination();
      }
      std::cout << "Computer moves from " << simplechess::column(from) << simplechess::row(from)
                << " to " << simplechess::column(to) << simplechess::row(to) << ".\n";
      if (!board.move(from, to, simplechess::PieceType::queen))
      {
        std::cout << "The computer move is not allowed!\n";
        return 2;
      }
    } // computer moves
  } //while

  return 0;
}
