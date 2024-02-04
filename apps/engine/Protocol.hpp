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

#ifndef SIMPLE_CHESS_PROTOCOL_HPP
#define SIMPLE_CHESS_PROTOCOL_HPP

namespace simplechess
{

enum class Protocol
{
  /// UCI (universal chess interface)
  UCI,

  /// XBoard protocol
  XBoard
};


/** \brief Tries to detect the used protocol by looking at the standard input.
 *
 * \return Returns the detected protocol, if successful.
 *         Throws if no protocol could be detected.
 */
Protocol detectProtocolFromStdIn();

} // namespace

#endif // SIMPLE_CHESS_PROTOCOL_HPP
