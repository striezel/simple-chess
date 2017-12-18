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

#include "io-utils.hpp"
#include <cerrno>
#include <iostream>
#include <unistd.h>

namespace simplechess
{

void disableStdinBuffering()
{
  std::cin.rdbuf()->pubsetbuf(nullptr, 0);
  std::cin.setf(std::ios_base::unitbuf);
}

void disableStdoutBuffering()
{
  std::cout.rdbuf()->pubsetbuf(nullptr, 0);
  std::cout.setf(std::ios_base::unitbuf);
}

void sendCommand(const std::string& cmd)
{
  if (cmd.empty())
    return;
  // Send via unbuffered system call.
  write(1, cmd.c_str(), cmd.size());
  write(1, "\n", 1);
}

} // namespace
