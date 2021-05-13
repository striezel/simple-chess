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
#include "IsReady.hpp"
#include "NewGame.hpp"
#include "Position.hpp"
#include "Quit.hpp"
#include "Uci.hpp"
#include "../Command.hpp"
#include "../Engine.hpp"
#include "../io-utils.hpp"

namespace simplechess::uci
{

void CommandParser::parse(const std::string& commandString)
{
  if (commandString.empty())
    return;
  if (commandString == "isready")
  {
    Engine::get().addCommand(std::unique_ptr<Command>(new IsReady()));
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
