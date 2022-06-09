/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016, 2017, 2018, 2022  Dirk Stolle

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

#ifndef SIMPLECHESS_UTIL_STRINGS_HPP
#define SIMPLECHESS_UTIL_STRINGS_HPP

#include <string>
#include <vector>

namespace simplechess::util
{

/** \brief Splits a string into several strings, using the given separator.
 *
 * \param line    the string that shall be split
 * \param separator   character that works as separator for parts / substrings
 * \return Returns a vector of strings, containing the split strings.
 */
std::vector<std::string> split(std::string line, const char separator = ' ');


/** \brief Tries to convert the string representation of an integer number into
 * an int and returns true on success, false on failure.
 *
 * \param str    the string that contains the number
 * \param value  the int that will be used to store the result
 * \return Returns true, if the string could be converted to integer.
 * \remarks If false is returned, the value of parameter value is undefined.
 */
bool stringToInt(const std::string& str, int& value);


/** \brief Removes all leading whitespace characters from the given string.
 *
 * \param str1   the affected string
 * \remarks The function works in place, i.e. it modifies the string directly.
 */
void trimLeft(std::string& str1);

} // namespace

#endif // SIMPLECHESS_UTIL_STRINGS_HPP
