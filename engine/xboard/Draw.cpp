/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2018  Dirk Stolle

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

#include "Draw.hpp"
#include "../Engine.hpp"
#include "../io-utils.hpp"

namespace simplechess
{

Draw::Draw()
{
  // Nothing to do here.
}

bool Draw::process()
{
  // If the opponent can claim a draw by 50 move rule, accept offer.
  if (Engine::get().board().halfmovesFifty() >= 100)
  {
    sendCommand("offer draw");
    return true;
  }
  // Accept draw only if the score is better for the opponent than for the
  // engine.
  Engine& eng = Engine::get();
  const int score = eng.evaluator().score(eng.board());
  if (((Engine::get().player() == Colour::white) && (score < -10))
    || ((Engine::get().player() == Colour::black) && (score > 10)))
  {
    // Accept draw.
    sendCommand("offer draw");
    return true;
  }
  // Do not accept, i.e. we need to do nothing here.
  return true;
}

} // namespace
