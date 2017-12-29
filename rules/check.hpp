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

#ifndef SIMPLE_CHESS_CHECK_HPP
#define SIMPLE_CHESS_CHECK_HPP

#include "../data/Board.hpp"
#include "../data/Piece.hpp"

namespace simplechess
{

/** \brief determines whether a field is attacked by a certain colour
 *
 * \param board  the current board
 * \param by     the attacking colour/player
 * \param field  the field which shall be checked
 * \return Returns true, if the given field is attacked by the given player.
 *         Returns false otherwise.
 */
bool isUnderAttack(const Board& board, const Colour by, const Field field);


/** \brief determines whether or not a player/colour is in check
 *
 * \param board   the current board
 * \param colour  the colour to check
 * \return Returns true, if the given colour is in check.
 *         Returns false otherwise.
 */
bool isInCheck(const Board& board, const Colour colour);


/** \brief determines whether or not a player/colour is checkmate
 *
 * \param board   the current board
 * \param colour  the colour to check
 * \return Returns true, if the given player is checkmate.
 *         Returns false otherwise.
 */
bool isCheckMate(const Board& board, const Colour colour);

} // namespace

#endif // SIMPLE_CHESS_CHECK_HPP
