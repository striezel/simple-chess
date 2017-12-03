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

#ifndef SIMPLECHESS_IO_UTILS_HPP
#define SIMPLECHESS_IO_UTILS_HPP

namespace simplechess
{

/** \brief Disables all buffering on std::cin.
 */
void disableStdinBuffering();


/** \brief Disables all buffering on std::cout.
 */
void disableStdoutBuffering();


/** \brief Checks whether std::cin has data to be read.
 *
 * \return Returns true, if there is data that can be read.
 *         Returns false otherwise.
 * \remarks This function returns immediately, if there is readable data.
 *          If there is no readable data yet, then this function waits for a
 *          small timespan (ca. 0.5 seconds) for data before returning.
 */
bool readableDataOnStandardInput();

} // namespace

#endif // SIMPLECHESS_IO_UTILS_HPP
