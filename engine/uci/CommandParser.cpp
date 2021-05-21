/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2021  Dirk Stolle

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
#include "Go.hpp"
#include "IsReady.hpp"
#include "Move.hpp"
#include "NewGame.hpp"
#include "Position.hpp"
#include "Quit.hpp"
#include "Uci.hpp"
#include "../Command.hpp"
#include "../Engine.hpp"
#include "../io-utils.hpp"

namespace simplechess::uci
{

const std::regex regExMove = std::regex("^([a-h][1-8])([a-h][1-8])([qbnr])?$");

void CommandParser::parse(const std::string& commandString)
{
  if (commandString.empty())
    return;
  std::smatch matches;
  if(std::regex_search(commandString, matches, regExMove))
  {
    const Field origin = toField(matches.str(1).at(0), matches.str(1).at(1) - '1' + 1);
    const Field destination = toField(matches.str(2).at(0), matches.str(2).at(1) - '1' + 1);
    PieceType promoteTo = PieceType::none;
    if (matches[3].matched)
    {
      if (matches.str(3) == "b")
        promoteTo = PieceType::bishop;
      else if (matches.str(3) == "n")
        promoteTo = PieceType::knight;
      else if (matches.str(3) == "q")
        promoteTo = PieceType::queen;
      else if (matches.str(3) == "r")
        promoteTo = PieceType::rook;
    }
    Engine::get().addCommand(std::unique_ptr<Command>(new Move(origin, destination, promoteTo)));
  } // move command
  else if (commandString == "isready")
  {
    Engine::get().addCommand(std::unique_ptr<Command>(new IsReady()));
  }
  else if (commandString == "go")
  {
    Engine::get().addCommand(std::unique_ptr<Command>(new Go()));
  }
  else if ((commandString == "ucinewgame") || (commandString == "position startpos"))
  {
    Engine::get().addCommand(std::unique_ptr<Command>(new NewGame()));
  }
  else if (commandString.substr(0, 13) == "position fen ")
  {
    Engine::get().addCommand(std::unique_ptr<Command>(new Position(commandString.substr(13))));
  }
  else if (commandString == "uci")
  {
    Engine::get().addCommand(std::unique_ptr<Command>(new Uci()));
  }
  else if (commandString == "quit")
  {
    Engine::get().addCommand(std::unique_ptr<Command>(new Quit()));
  }
  else
  {
    // Command is unknown / not supported. Those should be silently ignored,
    // according to the UCI specification. But let's give the user a hint.
    sendCommand("Error: Unknown command " + commandString);
  }
}

} // namespace
