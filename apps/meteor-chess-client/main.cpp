/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2018, 2019, 2020, 2024  Dirk Stolle

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

#include <iomanip>
#include <iostream>
#include <sstream>
#include "../../third-party/nlohmann/json.hpp"
#include "../../libsimple-chess/db/mongo/libmongoclient/Server.hpp"
#include "../../libsimple-chess/evaluation/CompoundCreator.hpp"
#include "../../libsimple-chess/evaluation/CompoundEvaluator.hpp"
#include "../../libsimple-chess/search/Search.hpp"
#include "../../libsimple-chess/rules/Moves.hpp"
#include "../../util/GitInfos.hpp"
#include "../../util/ReturnCodes.hpp"
#include "../../util/Version.hpp"
#include "Options.hpp"

void showVersion(const bool json = false)
{
  simplechess::GitInfos info;
  if (!json)
  {
    std::cout << "meteor-chess-client, " << simplechess::version << "\n"
              << "\n"
              << "Version control commit: " << info.commit() << "\n"
              << "Version control date:   " << info.date() << std::endl;
  }
  else
  {
    nlohmann::json val;
    val["version"]["major"] = simplechess::versionMajor;
    val["version"]["minor"] = simplechess::versionMinor;
    val["version"]["patch"] = simplechess::versionPatch;
    val["version"]["fullText"] = simplechess::version;
    val["commit"] = info.commit();
    val["date"] = info.date();
    std::cout << std::setw(4) << val << std::endl;
  }
}

void showHelp()
{
  std::cout << "meteor-chess-client [OPTIONS]\n"
            << "\n"
            << "options:\n"
            << "  --help | -?      - Shows this help message and exits.\n"
            << "  --version | -v   - Shows version information and exits.\n"
            << "  --board ID       - Sets the ID of the chess board that will be read.\n"
            << "                     This parameter is mandatory.\n"
            << "  --host hostname  - Sets the host name of the meteor-chess MongoDB server.\n"
            << "                     The default value is \"localhost\".\n"
            << "  --port N         - Sets the port number of the meteor-chess MongoDB server.\n"
            << "                     The default value is 3001.\n"
            << "  --json           - Prints output in JSON format.\n"
            << "  --move           - Perform move on board and write it back to MongoDB. The\n"
            << "                     default is not to move, but just to print the move.\n"
            << "  --evaluator EVAL - Sets a custom set of evaluators to use where EVAL is a\n"
            << "                     comma-separated list of evaluator ids. Valid ids are:\n"
            << "                       material: evaluator using material value of pieces\n"
            << "                       check: evaluator with bonus for checking opponent\n"
            << "                       castling: evaluator with malus for not castling before\n"
            << "                                 the possibility for castling is lost\n"
            << "                       promotion: evaluator with bonus for pawns that can be\n"
            << "                                  promoted during the next move\n"
            << "                       linearmobility: bonus for number of possible moves over\n"
            << "                                       all pieces by a player\n"
            << "                       rootmobility: like linearmobility, but with a slower\n"
            << "                                     increase for higher move numbers\n"
            << "                     A possible use of this option can look like this:\n"
            << "                       --evaluator check,promotion,material\n"
            << "                     If no evaluator option is given, the program uses a preset.\n";
}

int main(int argc, char** argv)
{
  simplechess::MeteorChessOptions options;
  if (!options.parse(argc, argv))
  {
    std::cout << "Invalid parameters encountered, program will exit.\n"
              << "Use --help to show recognized parameters.\n";
    return simplechess::rcInvalidParameter;
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
    showVersion(options.json);
    return 0;
  }
  // Is there a board id?
  if (options.boardId.empty())
  {
    std::cerr << "Error: No board id was set!\n";
    return simplechess::rcInvalidParameter;
  }

  // Prepare evaluators.
  simplechess::CompoundEvaluator evaluator;
  if (options.evaluators.empty())
  {
    // Fall back to default evaluator set.
    simplechess::CompoundCreator::getDefault(evaluator);
  }
  else
  {
    // Try to parse user input.
    if (!simplechess::CompoundCreator::create(options.evaluators, evaluator))
    {
      std::cerr << "Error: The given evaluator list is invalid!\n";
      return simplechess::rcInvalidParameter;
    }
  }

  try
  {
    simplechess::db::mongo::libmongoclient::Server server(options.hostname, options.port, true);
    simplechess::Board board;
    if (!server.getBoard(options.boardId, board))
    {
      std::cerr << "Could not get board data for board " << options.boardId
                << " from DB!\n";
      return simplechess::rcMongoDbError;
    }

    // Let's find a suitable move.
    simplechess::Search s(board);
    // Search for best move, only two plies.
    s.search(evaluator, 2);
    // Did the search find any moves?
    if (!s.hasMove())
    {
      if (options.json)
      {
        nlohmann::json val;
        val["resign"] = true;
        val["draw"] = false;
        val["message"] = std::string("simplechess engine could not find a valid move. User wins!");
        val["exitcode"] = simplechess::rcEngineResigns;
        std::cout << std::setw(4) << val << std::endl;
      }
      else
      {
        std::cout << "simplechess engine could not find a valid move. User wins!\n";
      }
      return simplechess::rcEngineResigns;
    } // if there is no move left

    // Claim draw under the 50 move rule?
    if (board.halfmovesFifty() >= 100)
    {
      if (options.json)
      {
        nlohmann::json val;
        val["resign"] = false;
        val["draw"] = true;
        val["message"] = std::string("Computer claims draw by 50 move rule.");
        val["exitcode"] = simplechess::rcEngineClaimsDraw;
        std::cout << std::setw(4) << val << std::endl;
      }
      else
      {
        std::cout << "Computer claims draw by 50 move rule!\n";
      }
      return simplechess::rcEngineClaimsDraw;
    }

    const auto bestMove = s.bestMove();
    const simplechess::Field from = std::get<0>(bestMove);
    const simplechess::Field to = std::get<1>(bestMove);
    const simplechess::PieceType promo = std::get<2>(bestMove);
    if (!options.json)
    {
      std::cout << "Computer moves from " << simplechess::column(from) << simplechess::row(from)
                << " to " << simplechess::column(to) << simplechess::row(to) << ".\n";
    }
    if (options.move)
    {
      if (!board.move(from, to, promo))
      {
        if (options.json)
        {
          nlohmann::json val;
          val["resign"] = true;
          val["draw"] = false;
          val["message"] = std::string("The computer move is not allowed! User wins.");
          val["exitcode"] = simplechess::rcEngineResigns;
          std::cout << std::setw(4) << val << std::endl;
        }
        else
        {
          std::cout << "The computer move is not allowed! User wins.\n";
        }
        return simplechess::rcEngineResigns;
      } // if move not possible
      if (!server.updateBoard(options.boardId, board))
      {
        std::cerr << "Could not update board in MongoDB!\n";
        return simplechess::rcMongoDbError;
      }
    } // if move shall be performed
    // print move in JSON
    if (options.json)
    {
      nlohmann::json val;
      val["resign"] = false;
      val["draw"] = (board.halfmovesFifty() >= 100);
      val["from"]["column"] = std::string(1, simplechess::column(from));
      val["from"]["row"] = simplechess::row(from);
      val["to"]["column"] = std::string(1, simplechess::column(to));
      val["to"]["row"] = simplechess::row(to);
      const bool isPromotion = simplechess::Moves::isPromotion(board, from, to);
      val["promotion"] = isPromotion;
      if (!isPromotion)
      {
        val["promoteTo"] = nullptr;
      }
      else
      {
        std::ostringstream stream;
        stream << promo;
        val["promoteTo"] = stream.str();
      }
      val["exitcode"] = 0;
      std::cout << std::setw(4) << val << std::endl;
    }
    // All is fine.
    return 0;
  } // try
  catch (const std::exception& ex)
  {
    const std::string reason = ex.what();
    std::cerr << "Error: An exception occurred!\n"
              << reason << "\n";
    if (reason.find("MongoDB") != std::string::npos)
    {
      std::cerr << "Hint: It seems that the error is related to MongoDB. "
                << "Please check that meteor-chess is running and its MongoDB "
                << "instance can be reached at " << options.hostname << ":" << options.port
                << ".\n";
      return simplechess::rcMongoDbError;
    }
    // Other error type.
    return simplechess::rcUnknown;
  }
}
