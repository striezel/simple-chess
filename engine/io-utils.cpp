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
#include <sys/select.h>
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


/** \brief Checks whether std::cin has data to be read.
 *
 * \return Returns true, if there is data that can be read.
 *         Returns false otherwise.
 * \remarks If there is no readable data yet, then this function waits for a
 *          small timespan (ca. 0.5 seconds) before returning.
 */
bool readableDataOnStandardInput()
{
  /*
  // poll() std::cin for input
  struct pollfd fd;
  fd.events = POLLIN;
  fd.fd = 0; // std::cin always has file descriptor zero.
  fd.revents = 0;
  const int timeout_msecs = 100;
  const int result = poll(&fd, 1, timeout_msecs);
  return (result > 0);
  */
  fd_set readFds;
  FD_ZERO(&readFds);
  FD_SET(0, &readFds); // std::cin always has file descriptor zero.
  struct timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 100 * 1000; // 100 milliseconds
  const int result = select(1, &readFds, nullptr, nullptr, &timeout);
  if (result < 0)
  {
    // An error occurred.
    switch (errno)
    {
      case EBADF:
           std::cerr << "Bad / invalid file descriptor!" << std::endl;
           break;
      case EINTR:
           std::cerr << "select() was interrupted!" << std::endl;
           break;
      case EINVAL:
           std::cerr << "An invalid parameter value was specified for select()!" << std::endl;
           break;
      default:
           std::cerr << "Unknown error (code " << static_cast<int>(errno) << "occurred during select()!" << std::endl;
           break;
    } // switch
    errno = 0;
    return false;
  } // if

  return (FD_ISSET(0, &readFds));
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
