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

#ifndef SIMPLE_CHESS_XBOARD_PING_HPP
#define SIMPLE_CHESS_XBOARD_PING_HPP

#include "../Command.hpp"
#include <string>

namespace simplechess::xboard
{

/** \brief Class that handles the ping command.
 */
class Ping : public Command
{
  public:
    /** \brief Constructor.
     *
     * \param num  the ping string, usually a number like "1"
     */
    Ping(const std::string& num);


    /** \brief Processes the command, i.e. performs required actions.
     *
     * \return True if command was processed successfully.
     */
    bool process() final;
  private:
    std::string number; /**< the ping number */
}; // class

} // namespace

#endif // SIMPLE_CHESS_XBOARD_PING_HPP
