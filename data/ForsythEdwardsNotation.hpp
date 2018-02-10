/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016, 2017, 2018  Dirk Stolle

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

#ifndef SIMPLECHESS_FEN_HPP
#define SIMPLECHESS_FEN_HPP

#include "Board.hpp"

namespace simplechess
{

/** \brief Class to create Forsyth-Edwards Notation (FEN) of a board. */
class ForsythEdwardsNotation
{
  public:
    /** \brief returns the Forsyth-Edwards-Notation for a board
     *
     * \param  board   the chess board
     * \return Returns a string that contains the FEN of the board.
     *         Returns an empty string, if the board contains invalid data.
     */
    static std::string fromBoard(const Board & board);


    /** \brief Forsyth-Edwards notation for the initial position in chess
     */
    static const std::string defaultInitialPosition;
}; // class

// type alias
typedef ForsythEdwardsNotation FEN;

} // namespace

#endif // SIMPLECHESS_FEN_HPP
