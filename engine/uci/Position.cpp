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

#include "Position.hpp"
#include "../io-utils.hpp"
#include "../Engine.hpp"
#include "../../data/ForsythEdwardsNotation.hpp"

namespace simplechess::uci
{

Position::Position(const std::string& fen)
: fen(fen)
{
}

bool Position::process()
{
  Board& board = Engine::get().board();
  // Reset the board to the standard chess starting position.
  if (!board.fromFEN(fen))
  {
    sendCommand("Error: invalid FEN given");
    return false;
  }
  // Leave force mode...
  Engine::get().setForceMode(false);
  // ... and set the engine to play the side that is to move.
  Engine::get().setPlayer(board.toMove());
  // Reset clocks and time controls to the start of a new game.
  Timing& timing = Engine::get().timing();
  timing.self().reset();
  timing.opponent().reset();
  // Use wall clock for time measurement. Stop clocks.
  timing.self().stop();
  timing.opponent().stop();
  // TODO: Do not ponder on this move, even if pondering is on.
  // Reset previously set limit on search depth.
  Engine::get().setSearchDepth(100);
  return true;
}

} // namespace
