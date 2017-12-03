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
#include "Engine.hpp"
#include "xboard/Command.hpp"
#include "xboard/Error.hpp"
#include "xboard/Quit.hpp"
#include "xboard/Xboard.hpp"

namespace simplechess
{

void CommandParser::parse(const std::string& commandString)
{
  if (commandString.empty())
    return;
  if (commandString == "xboard")
  {
    Engine::get().addCommand(std::unique_ptr<Command>(new Xboard()));
  }
  else if (commandString == "quit")
  {
    Engine::get().addCommand(std::unique_ptr<Command>(new Quit()));
  }
  else
  {
    Engine::get().addCommand(std::unique_ptr<Command>(new Error("unknown command", commandString)));
  }
}

} // namespace
