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

#include "New.hpp"
#include "../Engine.hpp"
#include "../../data/ForsythEdwardsNotation.hpp"

namespace simplechess::xboard
{

bool New::process()
{
  Board& board = Engine::get().board();
  // Reset the board to the standard chess starting position.
  if (!board.fromFEN(FEN::defaultInitialPosition))
  {
    return false;
  }
  // Set White on move.
  board.setToMove(Colour::white);
  // Leave force mode...
  Engine::get().setForceMode(false);
  // ... and set the engine to play Black.
  Engine::get().setPlayer(Colour::black);
  // Reset clocks and time controls to the start of a new game.
  Timing& timing = Engine::get().timing();
  timing.self().reset();
  timing.opponent().reset();
  // Use wall clock for time measurement. Stop clocks.
  timing.self().stop();
  timing.opponent().stop();
  // TODO: Do not ponder on this move, even if pondering is on.
  //       Remove any search depth limit previously set by the sd command.
  return true;
}

} // namespace
