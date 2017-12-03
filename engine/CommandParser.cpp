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

#include "CommandParser.hpp"
#include <regex>
#include "Engine.hpp"
#include "xboard/Command.hpp"
#include "xboard/Error.hpp"
#include "xboard/New.hpp"
#include "xboard/ProtocolVersion.hpp"
#include "xboard/Quit.hpp"
#include "xboard/Usermove.hpp"
#include "xboard/Xboard.hpp"
#include "../util/strings.hpp"

namespace simplechess
{

const std::regex regExMove = std::regex("^(usermove )?([a-h][1-8])([a-h][1-8])([qbnr])?$");

void CommandParser::parse(const std::string& commandString)
{
  if (commandString.empty())
    return;
  std::smatch matches;
  if(std::regex_search(commandString, matches, regExMove))
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
    // No operation required, we currently ignore this.
  }
  else
  {
    Engine::get().addCommand(std::unique_ptr<Command>(new Error("unknown command", commandString)));
  }
}

} // namespace
