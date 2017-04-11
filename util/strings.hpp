/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016, 2017  Dirk Stolle

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

#ifndef SIMPLE_CHESS_UTIL_STRINGS_HPP
#define SIMPLE_CHESS_UTIL_STRINGS_HPP

#include <string>
#include <vector>

namespace simplechess
{

namespace util
{

/** \brief splits a string into several strings, using the given separator
 *
 * \param line    the string that shall be split
 * \param separator   character that works as separator for parts / substrings
 * \return Returns a vector of strings, containing the split strings.
 */
std::vector<std::string> split(std::string line, const char separator = ' ');


/** \brief gets the string representation of an integer value
 *
 * \param value   integer value
 * \return Returns a string containing the given integer.
 */
std::string intToString(const int value);

} //namespace

} //namespace

#endif // SIMPLE_CHESS_UTIL_STRINGS_HPP
