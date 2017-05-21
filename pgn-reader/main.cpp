/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017  Dirk Stolle

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
#include <string>
#include <thread>
#include "Options.hpp"
#include "../algorithm/Apply.hpp"
#include "../data/Board.hpp"
#include "../data/ForsythEdwardsNotation.hpp"
#include "../data/PortableGameNotation.hpp"
#include "../pgn/Parser.hpp"
#include "../pgn/Tokenizer.hpp"
#include "../pgn/UnconsumedTokensException.hpp"
#include "../pgn/ParserException.hpp"
#include "../ui/Console.hpp"

void showHelp()
{
  std::cout << "\npgn-reader --pgn FILENAME [--delay MILLISECONDS]\n"
            << "\n"
            << "options:\n"
            << "  --help | -?      - displays this help message and quits\n"
            << "  -pgn FILENAME    - sets the path for the Portable Game Notation file that\n"
            << "                     will be read. This parameter is mandatory.\n"
            << "  --delay MS       - sets the delay between moves to MS milliseconds.\n"
            << "                     The default value is 1000, i.e. one second.\n";
}

int main(int argc, char** argv)
{
  simplechess::PgnReaderOptions options;
  if (!options.parse(argc, argv))
  {
    std::cout << "Invalid parameters encountered, program will exit.\n"
              << "Use --help to show recognized parameters.\n";
    return 1;
  }
  if (options.help)
  {
    showHelp();
    return 0;
  }
  if (options.inputFile.empty())
  {
    std::cout << "Error: No input file with portable game notation was given!\n";
    return 1;
  }

  std::vector<simplechess::pgn::Token> tokens;
  bool success = simplechess::pgn::Tokenizer::fromFile(options.inputFile, tokens);
  if (!success)
  {
    std::cout << "Could not tokenize PGN from file " + options.inputFile + "!\n";
    return 1;
  }
  simplechess::PortableGameNotation pgn;
  try
  {
    success = simplechess::pgn::Parser::parse(tokens, pgn);
  }
  catch(const simplechess::pgn::UnconsumedTokensException& ex)
  {
    std::cout << "UnconsumedTokensException: " << ex.what() << "\n";
    const auto & tokens = ex.unprocessedTokens();
    std::cout << "First unprocessed token: " << tokens.at(0).text << " of type "
              << static_cast<int>(tokens.at(0).type) << ".\n";
    std::cout << "All remaining tokens:\n";
    for (size_t i = 0; i < tokens.size(); ++i)
    {
      std::cout << "Type: " << static_cast<int>(tokens[i].type) << " text: \"" << tokens[i].text << "\"\n";
    } //for
    return 2;
  }
  catch(const simplechess::pgn::ParserException& ex)
  {
    std::cout << "ParserException: " << ex.what() << "\n";
    return 2;
  }
  std::cout << "Successfully parsed input data. :)\n";
  std::cout << "\n"
            << "PGN is:\n"
            << pgn.toString() << "\n";
  std::cout << "Number of first move: " << pgn.firstMoveNumber() << "\n"
            << "Number of last move:  " << pgn.lastMoveNumber() << "\n";

  //start game
  simplechess::Board board;
  std::string fen = simplechess::FEN::defaultInitialPosition;
  if (!pgn.tag("FEN").empty())
    fen = pgn.tag("FEN");

  if (!board.fromFEN(fen))
  {
    std::cout << "Could not initialize chess board with the given initial position!\n";
    return 3;
  }

  std::cout << "\n\nInitial position:\n\n";
  simplechess::ui::Console::showBoard(board);

  const std::chrono::milliseconds delay(options.delayMilliseconds);
  for (unsigned int i = pgn.firstMoveNumber(); i <= pgn.lastMoveNumber(); ++i)
  {
    std::this_thread::sleep_for(delay);
    const auto moves = pgn.move(i);
    if (!simplechess::algorithm::applyMove(board, moves.first, simplechess::Colour::white))
    {
      std::cout << "Error: Could not perform move " << i << " of white player!\n"
                << "Move would have been " << moves.first.toPGN() << ".\n";
      return 4;
    }
    std::cout << "\nAfter move " << i << " of white player:\n";
    simplechess::ui::Console::showBoard(board);

    std::this_thread::sleep_for(delay);
    if (!simplechess::algorithm::applyMove(board, moves.second, simplechess::Colour::black))
    {
      std::cout << "Error: Could not perform move " << i << " of black player!\n"
                << "Move would have been " << moves.second.toPGN() << ".\n";
      return 4;
    }
    std::cout << "\nAfter move " << i << " of black player:\n";
    simplechess::ui::Console::showBoard(board);
  } //for

  switch (pgn.result())
  {
    case simplechess::Result::Unknown:
         std::cout << "Outcome of the game is unknown.\n";
         break;
    default:
         std::cout << "Result of the game is " << pgn.resultToString(pgn.result()) << ".\n";
         break;
  } //switch

  return 0;
}
