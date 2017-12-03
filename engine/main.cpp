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

#include <iostream>
#include "io-utils.hpp"
#include "xboard/Error.hpp"

int main()
{
  using namespace simplechess;

  // No output buffering.
  disableStdoutBuffering();
  // No input buffering.
  disableStdinBuffering();

  bool quit = false;
  while (!quit)
  {
    const bool hasData = readableDataOnStandardInput();
    std::cout << "Result: " << static_cast<int>(hasData) << ".\n";
    if (hasData)
    {
      std::string command;
      std::getline(std::cin, command, '\n');
      // TODO: Implement command parsing.
      Error e = Error("unknown command", command);
      e.process();
    }
    break;
  } // while

  return 0;
}
