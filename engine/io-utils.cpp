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
#include <iostream>
#include <poll.h>

namespace simplechess
{

void disableStdinBuffering()
{
  std::cout.rdbuf()->pubsetbuf(nullptr, 0);
}

void disableStdoutBuffering()
{
  std::cin.rdbuf()->pubsetbuf(nullptr, 0);
}


/** \brief Checks whether std::cin has data to be read.
 *
 * \return Returns true, if there is data that can be read.
 *         Returns false otherwise.
 * \remarks If there is no readable data yet, then this function waits for a
 *          small timespan (ca. 0.5 seconds) before returning.
 */
bool readableDataOnStandardInput()
{
  // poll() std::cin for input
  struct pollfd fd;
  fd.events = POLLIN;
  fd.fd = 0; // std::cin always has file descriptor zero.
  fd.revents = 0;
  const int timeout_msecs = 500;
  const int result = poll(&fd, 1, timeout_msecs);
  return (result > 0);
}

} // namespace
