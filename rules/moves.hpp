/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016  Dirk Stolle

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

#ifndef SIMPLE_CHESS_MOVES_HPP
#define SIMPLE_CHESS_MOVES_HPP

#include "../data/board.hpp"
#include "../data/field.hpp"

namespace simplechess
{

class Moves
{
  public:
    static bool allowed(const Board& board, const Field from, const Field to);

    static void sanitizePromotion(PieceType& promoteTo);
}; //class

} //namespace

#endif // SIMPLE_CHESS_MOVES_HPP
