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

#ifndef SIMPLE_CHESS_IO_UTILS_HPP
#define SIMPLE_CHESS_IO_UTILS_HPP

#include <string>

namespace simplechess
{

/** \brief Disables all buffering on std::cin.
 */
void disableStdinBuffering();


/** \brief Disables all buffering on std::cout.
 */
void disableStdoutBuffering();


/** \brief Sends a command from the engine to xboard.
 *
 * \param cmd the command to send, excluding newline character
 * \remarks The command should be one line only.
 */
void sendCommand(const std::string& cmd);

} // namespace

#endif // SIMPLE_CHESS_IO_UTILS_HPP
