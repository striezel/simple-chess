/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2018, 2021  Dirk Stolle

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

#ifndef SIMPLE_CHESS_TERNARY_HPP
#define SIMPLE_CHESS_TERNARY_HPP

#include <cstdint>

namespace simplechess
{

  /** Enumeration for a ternary truth value (three-valued logic). */
  enum class Ternary: int_fast8_t { false_value = -1, maybe_value = 0, true_value = 1 };

} // namespace

#endif // SIMPLE_CHESS_TERNARY_HPP
