/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2022  Dirk Stolle

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

#ifndef SIMPLE_CHESS_UI_DETECT_UTF8_HPP
#define SIMPLE_CHESS_UI_DETECT_UTF8_HPP

namespace simplechess::ui
{

/** \brief Checks whether this system may support UTF-8 output on terminal.
 *
 * \remark This check is not very reliable, it only gives a rough indication.
 * \return Returns true, if the system seems to support UTF-8.
 */
bool may_support_utf8();

} // namespace

#endif // SIMPLE_CHESS_UI_DETECT_UTF8_HPP
