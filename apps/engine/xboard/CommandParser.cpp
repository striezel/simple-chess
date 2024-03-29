/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2018, 2021, 2022  Dirk Stolle

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

#include "CommandParser.hpp"
#include <regex>
#include "Draw.hpp"
#include "ExactTime.hpp"
#include "Error.hpp"
#include "Force.hpp"
#include "Go.hpp"
#include "Level.hpp"
#include "New.hpp"
#include "Ping.hpp"
#include "ProtocolVersion.hpp"
#include "Quit.hpp"
#include "ResultCmd.hpp"
#include "SetDepth.hpp"
#include "SetBoard.hpp"
#include "SetTime.hpp"
#include "Usermove.hpp"
#include "Xboard.hpp"
#include "../Command.hpp"
#include "../Engine.hpp"
#include "../../../libsimple-chess/data/Result.hpp"
#include "../../../util/strings.hpp"

namespace simplechess::xboard
{

const std::regex regExMove = std::regex("^(usermove )?([a-h][1-8])([a-h][1-8])([qbnr])?$");

void CommandParser::parse(const std::string& commandString)
{
  if (commandString.empty())
    return;
  std::smatch matches;
  if (std::regex_search(commandString, matches, regExMove))
  {
    const Field origin = toField(matches.str(2).at(0), matches.str(2).at(1) - '1' + 1);
    const Field destination = toField(matches.str(3).at(0), matches.str(3).at(1) - '1' + 1);
    PieceType promoteTo = PieceType::none;
    if (matches[4].matched)
    {
      if (matches.str(4) == "b")
        promoteTo = PieceType::bishop;
      else if (matches.str(4) == "n")
        promoteTo = PieceType::knight;
      else if (matches.str(4) == "q")
        promoteTo = PieceType::queen;
      else if (matches.str(4) == "r")
        promoteTo = PieceType::rook;
    }
    Engine::get().addCommand(std::unique_ptr<Command>(new Usermove(origin, destination, promoteTo)));
  } // usermove
  else if (commandString == "xboard")
  {
    // The "xboard" command is currently a no-op, but that might change in the future.
    Engine::get().addCommand(std::unique_ptr<Command>(new Xboard()));
  }
  else if (commandString == "quit")
  {
    Engine::get().addCommand(std::unique_ptr<Command>(new Quit()));
  }
  else if ((commandString.substr(0, 9) == "protover ") && (commandString.size() > 9))
  {
    int ver = -1;
    if (util::stringToInt(commandString.substr(9), ver))
    {
      Engine::get().addCommand(std::unique_ptr<Command>(new ProtocolVersion(ver)));
    }
    else
    {
      Engine::get().addCommand(std::unique_ptr<Command>(new Error("too few or invalid parameters", commandString)));
    }
  } // protover
  else if (commandString.substr(0, 9) == "accepted ")
  {
    // No operation required.
  }
  // random is a no-op for us (and basically for anyone except GNU Chess).
  else if (commandString == "random")
  {
    // No operation required.
  }
  else if (commandString == "computer")
  {
    // No operation required: Other player is a chess engine, too.
  }
  else if (commandString == "new")
  {
    Engine::get().addCommand(std::unique_ptr<Command>(new New()));
  }
  else if (commandString == "hard")
  {
    // Turn on pondering (i. e. "thinking" on the opponent's time).
    // No operation required, we currently ignore this.
  }
  else if (commandString == "easy")
  {
    // Turn off pondering.
    // No operation required, we currently do not support this.
    // Pondering is always off.
  }
  else if (commandString.substr(0, 6) == "level ")
  {
    const auto parts = util::split(commandString.substr(6), ' ');
    if (parts.size() < 3)
    {
      Engine::get().addCommand(std::unique_ptr<Command>(new Error("command expects three parameters", "level")));
      return;
    }
    int moves = -1;
    if (!util::stringToInt(parts[0], moves))
    {
      Engine::get().addCommand(std::unique_ptr<Command>(new Error("first parameter must be integer", commandString)));
      return;
    }
    std::chrono::seconds base = std::chrono::seconds::zero();
    const auto minSec = util::split(parts[1], ':');
    int minutes = -1;
    if (minSec.size() >= 1)
    {
      if (!util::stringToInt(minSec[0], minutes))
      {
        Engine::get().addCommand(std::unique_ptr<Command>(new Error("minute parameter must be an integer", commandString)));
        return;
      }
    }
    int seconds = 0;
    if (minSec.size() >= 2)
    {
      if (!util::stringToInt(minSec[1], seconds))
      {
        Engine::get().addCommand(std::unique_ptr<Command>(new Error("seconds parameter must be an integer", commandString)));
        return;
      }
    }
    base = std::chrono::seconds(60 * minutes + seconds);
    int increment = -1;
    if (!util::stringToInt(parts[2], increment))
    {
      Engine::get().addCommand(std::unique_ptr<Command>(new Error("increment parameter must be an integer", commandString)));
      return;
    }
    Engine::get().addCommand(std::unique_ptr<Command>(new Level(moves, base, std::chrono::seconds(increment))));
  }
  else if (commandString.substr(0, 3) == "st ")
  {
    int seconds = -1;
    if (!util::stringToInt(commandString.substr(3), seconds))
    {
      Engine::get().addCommand(std::unique_ptr<Command>(new Error("seconds parameter must be an integer", commandString)));
      return;
    }
    Engine::get().addCommand(std::unique_ptr<Command>(new ExactTime(std::chrono::seconds(seconds))));
  }
  else if (commandString.substr(0, 3) == "sd ")
  {
    int depth = -1;
    if (!util::stringToInt(commandString.substr(3), depth))
    {
      Engine::get().addCommand(std::unique_ptr<Command>(new Error("depth parameter must be an integer", commandString)));
      return;
    }
    if (depth < 1 || depth > 100)
    {
      Engine::get().addCommand(std::unique_ptr<Command>(new Error("depth parameter must be in range [0;100]", commandString)));
      return;
    }
    Engine::get().addCommand(std::unique_ptr<Command>(new SetDepth(depth)));
  }
  else if (commandString == "force")
  {
    // Switch to force mode.
    Engine::get().addCommand(std::unique_ptr<Command>(new Force()));
  }
  else if ((commandString == "post") || (commandString == "nopost"))
  {
    // No operation required, we currently ignore this.
  }
  else if (commandString == "go")
  {
    Engine::get().addCommand(std::unique_ptr<Command>(new Go()));
  }
  else if ((commandString.substr(0, 5) == "otim ") || (commandString.substr(0, 5) == "time "))
  {
    int centiS = -1;
    if (!util::stringToInt(commandString.substr(5), centiS))
    {
      Engine::get().addCommand(std::unique_ptr<Command>(new Error("parameter must be an integer", commandString)));
      return;
    }
    Engine::get().addCommand(std::unique_ptr<Command>(new SetTime(centiS, commandString.substr(0,4) == "otim")));
  }
  else if (commandString == "ping")
  {
    Engine::get().addCommand(std::unique_ptr<Command>(new Error("no ping number given", "ping")));
  }
  else if (commandString.substr(0, 5) == "ping ")
  {
    Engine::get().addCommand(std::unique_ptr<Command>(new Ping(commandString.substr(5))));
  }
  else if (commandString == "draw")
  {
    Engine::get().addCommand(std::unique_ptr<Command>(new Draw()));
  }
  else if (commandString.substr(0, 7) == "result ")
  {
    const std::vector<std::string> parts = util::split(commandString, ' ');
    Result res = Result::Unknown;
    if (parts.size() >= 2)
    {
      res = stringToResult(parts.at(1));
    } // result type
    std::string comment = "";
    if (parts.size() >= 3)
    {
      comment = parts[2];
      for (std::size_t i = 3; i < parts.size(); ++i)
      {
        comment += std::string(" ") + parts[i];
      }
    }
    Engine::get().addCommand(std::unique_ptr<Command>(new ResultCmd(res, comment)));
  }
  else if ((commandString.substr(0, 9) == "setboard ") && (commandString.size() > 9))
  {
    Engine::get().addCommand(std::unique_ptr<Command>(new SetBoard(commandString.substr(9))));
  }
  else
  {
    Engine::get().addCommand(std::unique_ptr<Command>(new Error("unknown command", commandString)));
  }
}

} // namespace
