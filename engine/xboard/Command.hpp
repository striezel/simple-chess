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

#ifndef SIMPLECHESS_XBOARD_COMMAND_HPP
#define SIMPLECHESS_XBOARD_COMMAND_HPP

namespace simplechess::xboard
{

/** Base class for all classes that handle XBoard protocol commands. */
class Command
{
  public:
    /** \brief Processes the command, i.e. performs required actions.
     *
     * \return True if command was processed successfully.
     * \remarks This method is pure virtual, i.e. each derived class has to
     *          override it and implement its own version of the method.
     */
    virtual bool process() = 0;


    /** \brief Virtual destructor (for derived classes).
     */
    virtual ~Command() = default;
}; // class

} // namespace

#endif // SIMPLECHESS_XBOARD_COMMAND_HPP
