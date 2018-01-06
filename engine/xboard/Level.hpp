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

#ifndef SIMPLECHESS_XBOARD_LEVEL_HPP
#define SIMPLECHESS_XBOARD_LEVEL_HPP

#include "Command.hpp"
#include <chrono>

namespace simplechess
{

/** Command for setting conventional or incremental timing mode. */
class Level: public Command
{
  public:
    /** \brief Constructor.
     *
     * \param moveCount number of moves
     * \param base base time (in seconds)
     * \param inc time increment (in seconds)
     */
    Level(const int moveCount, const std::chrono::seconds& base, const std::chrono::seconds& inc);


    /** \brief Processes the command, i.e. performs required actions.
     *
     * \return True if command was processed successfully.
     */
    virtual bool process() override;
  private:
    int moves; /**< number of moves (conventional mode) */
    std::chrono::seconds base; /**< base time (conventional or incremental mode) */
    std::chrono::seconds increment; /**< increment (incremental mode) */
}; // class

} // namespace

#endif // SIMPLECHESS_XBOARD_LEVEL_HPP
