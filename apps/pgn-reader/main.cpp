/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2018, 2022, 2024  Dirk Stolle

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
#include "../../libsimple-chess/algorithm/Apply.hpp"
#include "../../libsimple-chess/data/Board.hpp"
#include "../../libsimple-chess/data/ForsythEdwardsNotation.hpp"
#include "../../libsimple-chess/data/PortableGameNotation.hpp"
#ifndef NO_METEOR_CHESS
#include "../../libsimple-chess/db/mongo/Server.hpp"
#include "../../libsimple-chess/db/mongo/libmongoclient/Server.hpp"
#include <memory>
#endif // NO_METEOR_CHESS
#include "../../libsimple-chess/pgn/Parser.hpp"
#include "../../libsimple-chess/pgn/Tokenizer.hpp"
#include "../../libsimple-chess/pgn/UnconsumedTokensException.hpp"
#include "../../libsimple-chess/pgn/ParserException.hpp"
#include "../../libsimple-chess/ui/Console.hpp"
#include "../../libsimple-chess/ui/detect_utf8.hpp"
#include "../../util/ReturnCodes.hpp"

void showVersion()
{
  std::cout << "pgn-reader, version 0.9.1-u8, 2022-07-06" << std::endl;
  #ifndef NO_METEOR_CHESS
  std::cout << "This version has support for meteor-chess.\n";
  #endif // NO_METEOR_CHESS
}

void showHelp()
{
  std::cout << "\npgn-reader --pgn FILENAME [--delay MILLISECONDS]\n"
            << "\n"
            << "options:\n"
            << "  --help | -?      - Displays this help message and quits.\n"
            << "  --version | -v   - Shows version information and quits.\n"
            << "  --pgn FILENAME   - Sets the path for the Portable Game Notation file that\n"
            << "                     will be read. This parameter is mandatory.\n"
            << "  --delay N        - Sets the delay between moves to N milliseconds.\n"
            << "                     The default value is 1000, i.e. one second.\n";
  #ifndef NO_METEOR_CHESS
  std::cout << "  --meteor-chess   - Displays board in meteor-chess instance, too.\n"
            << "  --host hostname  - Sets host name of the meteor-chess MongoDB server.\n"
            << "                     The default value is \"localhost\".\n"
            << "  --port N         - Sets port number of the meteor-chess MongoDB server.\n"
            << "                     The default value is 3001.\n";
  #endif // NO_METEOR_CHESS
}

void showBoard(const simplechess::Board& board, const bool with_utf8)
{
  using namespace simplechess::ui;

  if (with_utf8)
  {
    Symbolic::showBoard(std::cout, board, Labels::Show);
  }
  else
  {
    Ascii::showBoard(std::cout, board, Labels::Show);
  }
}

int main(int argc, char** argv)
{
  simplechess::PgnReaderOptions options;
  if (!options.parse(argc, argv))
  {
    std::cout << "Invalid parameters encountered, program will exit.\n"
              << "Use --help to show recognized parameters.\n";
    return simplechess::rcInvalidParameter;
  }
  if (options.help)
  {
    showHelp();
    return 0;
  }
  if (options.version)
  {
    showVersion();
    return 0;
  }
  if (options.inputFile.empty())
  {
    std::cout << "Error: No input file with portable game notation was given!\n";
    return simplechess::rcInvalidParameter;
  }

  std::vector<simplechess::pgn::Token> tokens;
  bool success = simplechess::pgn::Tokenizer::fromFile(options.inputFile, tokens);
  if (!success)
  {
    std::cout << "Could not tokenize PGN from file " + options.inputFile + "!\n";
    return simplechess::rcTokenizationError;
  }
  simplechess::PortableGameNotation pgn;
  try
  {
    success = simplechess::pgn::Parser::parse(tokens, pgn);
  }
  catch(const simplechess::pgn::UnconsumedTokensException& ex)
  {
    std::cerr << "UnconsumedTokensException: " << ex.what() << "\n";
    const auto & tokens = ex.unprocessedTokens();
    std::cerr << "First unprocessed token: " << tokens.at(0).text << " of type "
              << static_cast<int>(tokens.at(0).type) << ".\n";
    std::cerr << "All remaining tokens:\n";
    for (size_t i = 0; i < tokens.size(); ++i)
    {
      std::cerr << "Type: " << static_cast<int>(tokens[i].type) << " text: \"" << tokens[i].text << "\"\n";
    } //for
    return simplechess::rcParserError;
  }
  catch(const simplechess::pgn::ParserException& ex)
  {
    std::cerr << "ParserException: " << ex.what() << "\n";
    return simplechess::rcParserError;
  }
  std::cout << "Successfully parsed input data. :)\n"
            << "\n"
            << "PGN is:\n"
            << pgn.toString() << "\n"
            << "Number of first move: " << pgn.firstMoveNumber() << "\n"
            << "Number of last move:  " << pgn.lastMoveNumber() << "\n";

  if (!simplechess::algorithm::checkPortableGameNotation(pgn))
  {
    std::cerr << "Error: Portable game notation data is implausible!\n";
    return simplechess::rcDataImplausible;
  }

  #ifndef NO_METEOR_CHESS
  //set default values for meteor-chess, if necessary
  if (options.meteorChess)
  {
    if (options.port == 0)
      options.port = 3001;
    if (options.hostname.empty())
      options.hostname = "localhost";
  }
  #endif // NO_METEOR_CHESS

  // start game
  simplechess::Board board;
  std::string fen = simplechess::FEN::defaultInitialPosition;
  if (!pgn.tag("FEN").empty())
    fen = pgn.tag("FEN");

  if (!board.fromFEN(fen))
  {
    std::cerr << "Could not initialize chess board with the given initial position!\n";
    return simplechess::rcBoardInitializationFailure;
  }

  #ifndef NO_METEOR_CHESS
  std::unique_ptr<simplechess::db::mongo::Server> mongo = nullptr;
  if (options.meteorChess)
  {
    try
    {
      auto mongoPtr = new simplechess::db::mongo::libmongoclient::Server(options.hostname, options.port, true);
      mongo = std::unique_ptr<simplechess::db::mongo::Server>(mongoPtr);
    }
    catch(...)
    {
      std::cerr << "Error: Could not establish connection to MongoDB on "
                << options.hostname << ":" << options.port << "!\n";
      return simplechess::rcMongoDbError;
    }
  } //if

  std::string boardId;
  #endif // NO_METEOR_CHESS

  const bool use_utf8 = simplechess::ui::may_support_utf8();

  std::cout << "\n\nInitial position:\n\n";
  showBoard(board, use_utf8);

  #ifndef NO_METEOR_CHESS
  if (options.meteorChess)
  {
    try
    {
      boardId = mongo->insertBoard(board);
    }
    catch(...)
    {
      std::cerr << "Error: Could not insert board into MongoDB on "
                << options.hostname << ":" << options.port << "!\n";
      mongo = nullptr;
      return simplechess::rcMongoDbError;
    }
    if (boardId.empty())
    {
      std::cerr << "Error: Could not insert board into MongoDB on "
                << options.hostname << ":" << options.port << ", empty ID!\n";
      mongo = nullptr;
      return simplechess::rcMongoDbError;
    }
    std::cout << "Inserted board ID is " << boardId << ".\n";
  } //if
  #endif // NO_METEOR_CHESS

  const std::chrono::milliseconds delay(options.delayMilliseconds);
  for (unsigned int i = pgn.firstMoveNumber(); i <= pgn.lastMoveNumber(); ++i)
  {
    std::this_thread::sleep_for(delay);
    const auto moves = pgn.move(i);
    if (!simplechess::algorithm::applyMove(board, moves.first, simplechess::Colour::white))
    {
      std::cerr << "Error: Could not perform move " << i << " of white player!\n"
                << "Move would have been " << moves.first.toPGN() << ".\n";
      return simplechess::rcMoveNotPossible;
    }
    std::cout << "\nAfter move " << i << " of white player:\n";
    showBoard(board, use_utf8);
    #ifndef NO_METEOR_CHESS
    if (options.meteorChess)
    {
      try
      {
        if (!mongo->updateBoard(boardId, board))
        {
          std::cerr << "Error: Could not update board in MongoDB on "
                    << options.hostname << ":" << options.port << "!\n";
          mongo = nullptr;
          return simplechess::rcMongoDbError;
        } //if
      }
      catch(...)
      {
        std::cerr << "Error: Failed to update board in MongoDB on "
                  << options.hostname << ":" << options.port << "!\n";
        mongo = nullptr;
        return simplechess::rcMongoDbError;
      }
    } //if
    #endif // NO_METEOR_CHESS

    std::this_thread::sleep_for(delay);
    if (!simplechess::algorithm::applyMove(board, moves.second, simplechess::Colour::black))
    {
      std::cerr << "Error: Could not perform move " << i << " of black player!\n"
                << "Move would have been " << moves.second.toPGN() << ".\n";
      return simplechess::rcMoveNotPossible;
    }
    std::cout << "\nAfter move " << i << " of black player:\n";
    showBoard(board, use_utf8);
    #ifndef NO_METEOR_CHESS
    if (options.meteorChess)
    {
      try
      {
        if (!(mongo->updateBoard(boardId, board)))
        {
          std::cerr << "Error: Could not update board in MongoDB on "
                    << options.hostname << ":" << options.port << "!\n";
          mongo = nullptr;
          return simplechess::rcMongoDbError;
        } //if
      }
      catch(...)
      {
        std::cerr << "Error: Failed to update board in MongoDB on "
                  << options.hostname << ":" << options.port << "!\n";
        mongo = nullptr;
        return simplechess::rcMongoDbError;
      }
    } //if
    #endif // NO_METEOR_CHESS
  } //for

  switch (pgn.result())
  {
    case simplechess::Result::Unknown:
         std::cout << "Outcome of the game is unknown.\n";
         break;
    default:
         std::cout << "Result of the game is " << simplechess::resultToString(pgn.result()) << ".\n";
         break;
  } //switch

  return 0;
}
