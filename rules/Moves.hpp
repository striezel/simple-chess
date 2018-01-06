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

#include "../data/Board.hpp"
#include "../data/Field.hpp"

namespace simplechess
{
/** class to check conformity of moves to rules */
class Moves
{
  public:
    /** \brief Checks whether a move is allowed.
     *
     * \param board  the chess board
     * \param from   field where the move begins
     * \param to     field where the move ends (destination)
     * \return Returns true, if the move is allowed. Returns false otherwise.
     */
    static bool allowed(const Board& board, const Field from, const Field to);


    /** \brief Sanitizes selected promotion piece type.
     *
     * \param promoteTo   the type of piece a pawn should get promoted to
     * \remarks The value of promoteTo will be changed to an allowed value, if
     *          it does not conform to promotion rules.
     */
    static void sanitizePromotion(PieceType& promoteTo);


    /** \brief Checks whether a move will cause a pawn promotion.
     *
     * \param board  the chess board
     * \param from   field where the move begins
     * \param to     field where the move ends (destination)
     * \return Returns true, if the move is a pawn promotion.
     *         Returns false otherwise.
     * \remarks Note that this method will _not_ check whether the move is
     *          allowed. It just checks whether the move would be a pawn
     *          promotion, were it allowed.
     */
    static bool isPromotion(const Board& board, const Field from, const Field to);


    /** \brief Move a piece on the given board.
     *
     * \param board  the chess board where the move shall be performed
     * \param from field where the move starts
     * \param to   field where the move ends
     * \param promoteTo type of piece that a pawn shall be promoted to, if the
     *                  move allows pawn promotion
     * \return Returns true, if the move was performed.
     * Returns false, if the move was not performed, e.g. because the move was
     * against the chess rules.
     */
    static bool performMove(Board& board, const Field from, const Field to, PieceType promoteTo);
}; // class

} // namespace

#endif // SIMPLE_CHESS_MOVES_HPP
