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

#ifndef SIMPLECHESS_COMMANDPARSER_HPP
#define SIMPLECHESS_COMMANDPARSER_HPP

#include <string>

namespace simplechess
{

/** Class that can parse xboard commands received from standard input. */
class CommandParser
{
  public:
    /** \brief Parses the given command.
     *
     * \param commandString  the string received via standard input (one line only)
     */
    static void parse(const std::string& commandString);
}; // class

} // namespace

#endif // SIMPLECHESS_COMMANDPARSER_HPP
