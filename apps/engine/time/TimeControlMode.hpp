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

#ifndef SIMPLE_CHESS_TIMECONTROLMODE_HPP
#define SIMPLE_CHESS_TIMECONTROLMODE_HPP

namespace simplechess
{

/** Enumeration type for the different time control modes. */
enum class TimeControlMode {
    // Conventional timing mode: get a fixed amount of time in which a fixed
    // number of moves has to be made; e.g. 5 minutes for 40 moves, which means
    // the engine can spend on average 5 * 60 seconds / 40 = 7.5 seconds for
    // thinking about a move.
    conventional,

    // Incremental timing mode: Gets a base amount from start plus an increment
    // for each move; e.g. 2 min base time + 10 seconds for each move. That
    // would imply for a game of 40 moves the engine can spend an average of
    // 2 * 60 seconds / 40 + 10 seconds = 13 seconds on every move.
    incremental,

    // Exact timing mode: Gives an exact number of seconds which the engine can
    // spend thinking on a move; e.g. 30 seconds per move. Time that has not
    // been used for a move will not get carried over to next move. That is, if
    // the engine only needs 20 seconds to decide on the best move, the remaining
    // ten seconds are lost.
    exact };

} // namespace

#endif // SIMPLE_CHESS_TIMECONTROLMODE_HPP
