/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2021  Dirk Stolle

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

#ifndef SIMPLECHESS_XBOARD_SETTIME_HPP
#define SIMPLECHESS_XBOARD_SETTIME_HPP

#include "../Command.hpp"

namespace simplechess::xboard
{

/** \brief Class that handles the ping command.
 */
class SetTime : public Command
{
  public:
    /** \brief Constructor.
     *
     * \param centiseconds  the number of centiseconds to set
     * \param opponent      whether the centiseconds are for the opponent
     */
    SetTime(const int centiseconds, const bool opponent);


    /** \brief Processes the command, i.e. performs required actions.
     *
     * \return True if command was processed successfully.
     */
    bool process() final;
  private:
    int mCentiseconds; /**< amount of centiseconds left */
    bool mOpponent; /**< true for opponent, false for engine time */
}; // class

} // namespace


#endif // SIMPLECHESS_XBOARD_SETTIME_HPP
