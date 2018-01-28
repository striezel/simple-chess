/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2018  Dirk Stolle

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
#include "../db/mongo/libmongoclient/Server.hpp"
#include "../evaluation/CheckEvaluator.hpp"
#include "../evaluation/CompoundEvaluator.hpp"
#include "../evaluation/MaterialEvaluator.hpp"
#include "../evaluation/LinearMobilityEvaluator.hpp"
#include "../evaluation/PromotionEvaluator.hpp"
#include "../search/Search.hpp"
#include "../util/GitInfos.hpp"
#include "../util/Version.hpp"
#include "Options.hpp"

const int rcInvalidParameter = 1;
const int rcEngineResigns = 2;
const int rcMongoDbError = 7;
const int rcUnknown = 8;

void showVersion()
{
  simplechess::GitInfos info;
  std::cout << "meteor-chess-client, " << simplechess::version << "\n"
            << "\n"
            << "Version control commit: " << info.commit() << "\n"
            << "Version control date:   " << info.date() << std::endl;
}

void showHelp()
{
  std::cout << "meteor-chess-client [OPTIONS]\n"
            << "\n"
            << "options:\n"
            << "  -? | --help      - shows this help message and exits\n"
            << "  -v | --version   - shows version information and exits\n"
            << "  --board ID       - sets the ID of the chess board that will be read.\n"
            << "                     This parameter is mandatory.\n"
            << "  --host hostname  - host name of the meteor-chess MongoDB server. The default\n"
            << "                     value is \"localhost\".\n"
            << "  --port N         - port number of the meteor-chess MongoDB server. The\n"
            << "                     default value is 3001.\n";
}

int main(int argc, char** argv)
{
  simplechess::MeteorChessOptions options;
  if (!options.parse(argc, argv))
  {
    std::cout << "Invalid parameters encountered, program will exit.\n"
              << "Use --help to show recognized parameters.\n";
    return rcInvalidParameter;
  }
  // Help requested?
  if (options.help)
  {
    showHelp();
    return 0;
  }
  // Version information requested?
  if (options.version)
  {
    showVersion();
    return 0;
  }
  // Is there a board id?
  if (options.boardId.empty())
  {
    std::cout << "Error: No board id was set!\n";
    return rcInvalidParameter;
  }

  try
  {
    simplechess::db::mongo::libmongoclient::Server server(options.hostname, options.port, true);
    simplechess::Board board;
    if (!server.getBoard(options.boardId, board))
    {
      std::cerr << "Could not get board data for board " << options.boardId
                << " from DB!" << std::endl;
      return rcMongoDbError;
    }

    // Let's find a suitable move.
    simplechess::Search s(board);
    simplechess::CompoundEvaluator evaluator;
    // Add the four evaluators we have so far.
    evaluator.add(std::unique_ptr<simplechess::Evaluator>(new simplechess::MaterialEvaluator()));
    evaluator.add(std::unique_ptr<simplechess::Evaluator>(new simplechess::LinearMobilityEvaluator()));
    evaluator.add(std::unique_ptr<simplechess::Evaluator>(new simplechess::PromotionEvaluator()));
    evaluator.add(std::unique_ptr<simplechess::Evaluator>(new simplechess::CheckEvaluator()));
    // Search for best move, only two plies.
    s.search(evaluator, 2);
    // Did the search find any moves?
    if (!s.hasMove())
    {
      std::cout << "simplechess AI could not find a valid move. User wins!\n";
      return rcEngineResigns;
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
      return rcEngineResigns;
    }
    if (!server.updateBoard(options.boardId, board))
    {
      std::cout << "Could not update board in MongoDB!\n";
      return rcMongoDbError;
    }
  } // try
  catch (const std::exception& ex)
  {
    const std::string reason = ex.what();
    std::cout << "Error: An exception occurred!\n"
              << reason << "\n";
    if (reason.find("MongoDB") != std::string::npos)
    {
      std::cout << "Hint: It seems that the error is related to MongoDB. "
                << "Please check that meteor-chess is running and its MongoDB "
                << "instance can be reached at " << options.hostname << ":" << options.port
                << ".\n";
      return rcMongoDbError;
    }
    // Other error type.
    return rcUnknown;
  } // try-catch
  return 0;
}
