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

#ifndef SIMPLECHESS_XBOARD_ERROR_HPP
#define SIMPLECHESS_XBOARD_ERROR_HPP

#include "Command.hpp"
#include <string>

namespace simplechess
{

/** \brief Class for unknown / illegal / erroneous commands that cannot be
 *         processed by the engine.
 */
class Error : public Command
{
  public:
    /** \brief Constructor.
     *
     * \param type the type of the error
     * \param command the original command from xboard
     */
    Error(const std::string& type, const std::string& command);


    /** \brief Processes the command, i.e. performs required actions.
     *
     * \return True if command was processed successfully.
     */
    virtual bool process() override;
  private:
    std::string mType; /**< type of error */
    std::string mCommand; /**< original command that caused the error */
}; // class

} // namespace

#endif // SIMPLECHESS_XBOARD_ERROR_HPP
