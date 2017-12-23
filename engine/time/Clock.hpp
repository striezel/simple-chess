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

#ifndef SIMPLECHESS_CLOCK_HPP
#define SIMPLECHESS_CLOCK_HPP

#include <chrono>

namespace simplechess
{

/** Type alias for centiseconds duration type. */
typedef std::chrono::duration<int64_t, std::centi> centiseconds;


/** \brief Represents a chess clock that is like a stopwatch that counts down.
 *
 * This Clock class is different from C++ concept Clock in various ways:
 * As wall time passes, the time points do not increase but decrease.
 * Furthermore, the time on the clock does not run all the time, but it can be
 * started and stopped instead.
 */
class Clock
{
  public:
    /** \brief Constructs a new Clock instance.
     *
     * \param initialTime the initial time amount that is on the clock
     */
    Clock(const centiseconds& initialTime);


    /** \brief Starts the clock, i.e. starts counting down.
     */
    void start();


    /** \brief Stops the clock, i.e. stops the countdown.
     */
    void stop();


    /** \brief Indicates whether the clock is currently running.
     *
     * \return true if the clock is currently running, false otherwise
     */
    bool running() const;


    /** \brief Gets the time that remains on the clock in centiseconds.
     *
     * \return remaining time on the clock in centiseconds
     */
    centiseconds remaining() const;


    /** \brief Gets the time that has elapsed since the last start in centiseconds.
     *
     * \return elapsed time since start in centiseconds
     */
    centiseconds elapsed() const;


    /** \brief Stops the clock and resets the remaining time to the initial amount.
     */
    void reset();


    /** \brief Stops the clock and resets the remaining time to the initial amount.
     *
     * \param initialAmount the new intial amount to which the clock will be reset
     */
    void reset(const centiseconds& initialAmount);
  private:
    centiseconds mInitial; /**< initial amount of time */
    centiseconds mRemaining; /**< remaining time on the clock */
    bool mRunning; /**< whether the clock is currently running */
    std::chrono::time_point<std::chrono::steady_clock> mStart; /**< time point when start was invoked */
}; // class

} // namespace

#endif // SIMPLECHESS_CLOCK_HPP
