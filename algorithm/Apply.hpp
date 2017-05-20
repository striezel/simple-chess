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

#ifndef SIMPLECHESS_ALGORITHM_APPLY_HPP
#define SIMPLECHESS_ALGORITHM_APPLY_HPP

#include "../data/Board.hpp"
#include "../data/HalfMove.hpp"

namespace simplechess
{

namespace algorithm
{

/** \brief applies a half move to a given board
 *
 * \param board the board where the move shall be applied
 * \param hMove half move that shall be applied
 * \param toMove player that moves
 * \return Returns true, if the move could be applied.
 *         Returns false otherwise.
 */
bool applyMove(Board& board, const HalfMove& hMove, const Colour toMove);


/** \brief finds the origin field for a half move
 *
 * \param board the board on which the half move will be performed
 * \param hMove next half move
 * \return Returns the first matching field, if it was found.
 *         Returns none, if no matching field was found
 */
Field findOriginField(const Board& board, const HalfMove& hMove);

} //namespace

} //namespace

#endif // SIMPLECHESS_ALGORITHM_APPLY_HPP
