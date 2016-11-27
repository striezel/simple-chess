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

#ifndef SIMPLE_CHESS_FEN_HPP
#define SIMPLE_CHESS_FEN_HPP

#include "board.hpp"

namespace simplechess
{

class ForsythEdwardsNotation
{
  public:
    /** \brief returns the Forsyth-Edwards-Notation for a board
     *
     * \param  board   the chess board
     * \return string that contains the FEN of the board
     */
    static std::string fromBoard(const Board & board);
}; //class

//type alias
typedef ForsythEdwardsNotation FEN;

} //namespace

#endif // SIMPLE_CHESS_FEN_HPP
