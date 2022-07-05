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

#ifndef SIMPLE_CHESS_RESULT_HPP
#define SIMPLE_CHESS_RESULT_HPP

#include <string>

namespace simplechess
{

/** enumeration value to denote the result of a chess game */
enum class Result { Unknown, WhiteWins, BlackWins, Draw };


/** \brief Gets the string representation of a result.
 *
 * \param res   the result
 * \return Returns a string indicating the result.
 */
std::string resultToString(const Result& res);


/** \brief Converts the string representation of a result into an enumeration value.
 *
 * \param res   the result as string
 * \return Returns a enumeration value indicating the result.
 */
Result stringToResult(const std::string& res);

} // namespace

#endif // SIMPLE_CHESS_RESULT_HPP
