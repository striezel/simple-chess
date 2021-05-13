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

#ifndef SIMPLECHESS_XBOARD_RESULTCMD_HPP
#define SIMPLECHESS_XBOARD_RESULTCMD_HPP

#include "../Command.hpp"
#include <string>
#include "../../data/Result.hpp"

namespace simplechess::xboard
{

/** \brief Class for that handles the result command.
 */
class ResultCmd : public Command
{
  public:
    /** \brief Constructor.
     *
     * \param res result of the game
     * \param comment comment / reason for result
     */
    ResultCmd(const Result res, const std::string& comment);


    /** \brief Processes the command, i.e. performs required actions.
     *
     * \return True if command was processed successfully.
     */
    bool process() final;
  private:
    Result result; /**< result of the game */
    std::string comment; /**< the comment, if any */
}; // class

} // namespace

#endif // SIMPLECHESS_XBOARD_RESULTCMD_HPP
