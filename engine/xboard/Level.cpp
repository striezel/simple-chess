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

#include "Level.hpp"
#include "../Engine.hpp"
#include "../io-utils.hpp"

namespace simplechess
{

Level::Level(const int moveCount, const std::chrono::seconds& base, const std::chrono::seconds& inc)
: moves(moveCount),
  base(base),
  increment(inc)
{
}

bool Level::process()
{
  if (moves > 0)
  {
    // conventional mode
    Timing& timing = Engine::get().timing();
    timing.setMode(TimeControlMode::conventional);
    timing.setConventional(moves, base);
    return true;
  }
  else if (moves == 0)
  {
    // incremental mode
    Timing& timing = Engine::get().timing();
    timing.setMode(TimeControlMode::incremental);
    timing.setIncremental(base, increment);
    return true;
  }
  else
  {
    // syntax error
    sendCommand("Error (incorrect command syntax, moves is less than zero): level");
    return true;
  }
}

} // namespace
