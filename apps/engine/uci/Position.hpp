/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2021  Dirk Stolle

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

#ifndef SIMPLE_CHESS_UCI_POSITION_HPP
#define SIMPLE_CHESS_UCI_POSITION_HPP

#include "../Command.hpp"
#include <string>

namespace simplechess::uci
{

/** Command for initializing a new position via "position fen ...". */
class Position: public Command
{
  public:
    /** \brief Initializes a new position with given FEN.
     *
     * \param fen   the Forsyth-Edwards Notation of the position
     */
    Position(const std::string& fen);


    /** \brief Processes the command, i.e. performs required actions.
     *
     * \return True if command was processed successfully.
     */
    bool process() final;
  private:
    std::string fen; /**< the FEN for the new position */
}; // class

} // namespace

#endif // SIMPLE_CHESS_UCI_POSITION_HPP
