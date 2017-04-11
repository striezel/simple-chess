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

#ifndef SIMPLE_CHESS_MOVES_HPP
#define SIMPLE_CHESS_MOVES_HPP

#include "../data/board.hpp"
#include "../data/field.hpp"

namespace simplechess
{
/** class to check conformity of moves to rules */
class Moves
{
  public:
    /** \brief checks whether a move is allowed
     *
     * \param board  the chess board
     * \param from   field where the move begins
     * \param to     field where the move ends (destination)
     * \return Returns true, if the move is allowed. Returns false otherwise.
     */
    static bool allowed(const Board& board, const Field from, const Field to);


    /** \brief sanitizes piece selected promotion piece type
     *
     * \param promoteTo   the type of piece a pawn should get promoted to
     * \remarks The value of promoteTo will be changed to an allowed value, if
     *          it does not conform to promotion rules.
     */
    static void sanitizePromotion(PieceType& promoteTo);
}; //class

} //namespace

#endif // SIMPLE_CHESS_MOVES_HPP
