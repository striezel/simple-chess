/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2018, 2021  Dirk Stolle

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

#ifndef SIMPLE_CHESS_XBOARD_PROTOCOLVERSION_HPP
#define SIMPLE_CHESS_XBOARD_PROTOCOLVERSION_HPP

#include "../Command.hpp"

namespace simplechess::xboard
{

/** \brief Class for that handles the protover command from XBoard.
 */
class ProtocolVersion: public Command
{
  public:
    /** \brief Constructor.
     *
     * \param protoVer the protocol version
     */
    ProtocolVersion(const unsigned int protoVer);

    /** \brief Processes the command, i.e. performs required actions.
     *
     * \return True if command was processed successfully.
     */
    bool process() final;
  private:
    unsigned int protocolVersion; /**< protocol version */
}; // class

} // namespace

#endif // SIMPLE_CHESS_XBOARD_PROTOCOLVERSION_HPP
