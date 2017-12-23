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

#ifndef SIMPLECHESS_TIMING_HPP
#define SIMPLECHESS_TIMING_HPP

#include <chrono>
#include <ratio>
#include "Clock.hpp"
#include "TimeControlMode.hpp"

namespace simplechess
{

/** \brief Class to handle all timing-related tasks
 */
class Timing
{
  public:
    /** \brief Default constructor.
     */
    Timing();


    /** \brief Gets the current time control mode.
     *
     * \return current time control mode
     */
    TimeControlMode mode() const;


    /** \brief Sets a new time control mode.
     *
     * \param newMode the new time control mode to set
     */
    void setMode(const TimeControlMode newMode);


    /** \brief Gets the clock for the engine.
     *
     * \return clock for the engine
     */
    Clock& self();


    /** \brief Gets the clock for the opponent.
     *
     * \return clock for the opponent
     */
    Clock& opponent();


    /** \brief Sets parameters for conventional timing mode.
     *
     * \param moves number of moves
     * \param time amount of time for these moves
     */
    void setConventional(const int moves, const std::chrono::seconds& time);


    /** \brief Sets the parameters for incremental timing mode.
     *
     * \param base base amount of time in seconds
     * \param increment incremental time for each move in seconds
     */
    void setIncremental(const std::chrono::seconds& base, const std::chrono::seconds& increment);


    /** \brief Sets the parameters for exact timing mode.
     *
     * \param secondsPerMove number of seconds per move
     */
    void setExact(const std::chrono::seconds& secondsPerMove);
  private:
    TimeControlMode mMode; /**< current time control mode */
    Clock mSelfClock; /**< clock of the engine */
    Clock mOpponentClock; /**< clock of the opponent */
    // conventional mode settings
    int mConventionalMoves; /**< number of moves in conventional timing mode */
    std::chrono::seconds mConventionalTime; /**< total time for all moves in conventional mode */
    // incremental mode settings
    std::chrono::seconds mIncrementalBase; /**< base time in incremental mode */
    std::chrono::seconds mIncrementalIncrement; /**< increment per move in incremental mode */
    // exact mode settings
    std::chrono::seconds mExactSecondsPerMove; /**< seconds per move in exact mode */
}; // class

} // namespace

#endif // SIMPLECHESS_TIMING_HPP
