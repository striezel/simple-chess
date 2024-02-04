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

#include "Protocol.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

namespace simplechess
{

Protocol detectProtocolFromStdIn()
{
  std::string initialLine;
  while (initialLine.empty())
  {
    std::getline(std::cin, initialLine, '\n');
  }

  if (initialLine == "uci")
    return Protocol::UCI;

  if (initialLine == "xboard")
    return Protocol::XBoard;

  throw std::invalid_argument(initialLine);
}

} // namespace
