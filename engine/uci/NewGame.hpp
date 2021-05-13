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

#ifndef SIMPLECHESS_UCI_NEWGAME_HPP
#define SIMPLECHESS_UCI_NEWGAME_HPP

#include "../Command.hpp"

namespace simplechess::uci
{

/** Command for initializing a new game / handling ucinewgame. */
class NewGame: public Command
{
  public:
    NewGame() = default;


    /** \brief Processes the command, i.e. performs required actions.
     *
     * \return True if command was processed successfully.
     */
    bool process() final;
}; // class

} // namespace

#endif // SIMPLECHESS_UCI_NEWGAME_HPP
