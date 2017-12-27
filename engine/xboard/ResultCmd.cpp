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

#include "ResultCmd.hpp"
#include "../Engine.hpp"

namespace simplechess
{

ResultCmd::ResultCmd(const Result res, const std::string& comment)
: result(res),
  comment(comment)
{
}

bool ResultCmd::process()
{
  /* Note: We might want to create and save a PGN file of the game here for
     further analysis, but that requires that the moves are recorded by the
     engine in the first place. They are not (yet). */

  // stop clocks
  Engine::get().timing().self().stop();
  Engine::get().timing().opponent().stop();

  // Reset board and the one side that is played by the engine.
  Engine::get().board() = Board();
  Engine::get().setPlayer(Colour::none);
  Engine::get().setForceMode(false);
  return true;
}

} // namespace
