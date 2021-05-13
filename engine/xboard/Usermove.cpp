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

#include "Usermove.hpp"
#include <sstream>
#include "../io-utils.hpp"
#include "../Engine.hpp"
#include "../../rules/Moves.hpp"

namespace simplechess::xboard
{

Usermove::Usermove(const Field ori, const Field dest, const PieceType promo)
: origin(ori),
  destination(dest),
  promoteTo(promo)
{
}

bool Usermove::process()
{
  Engine& engine = Engine::get();
  Board& b = engine.board();
  // perform move
  if (!b.move(origin, destination, promoteTo))
  {
    std::ostringstream oss;
    oss << "Illegal move: " << column(origin) << row(origin)
        << column(destination) << row(destination);
    switch (promoteTo)
    {
      case PieceType::queen:
           oss << "q";
           break;
      case PieceType::bishop:
           oss << "b";
           break;
      case PieceType::knight:
           oss << "n";
           break;
      case PieceType::rook:
           oss << "r";
           break;
      default:
           break;
    } // switch
    sendCommand(oss.str());
    return true;
  }
  // Stop opponent's clock.
  engine.timing().opponent().stop();

  // Make own move, but only if not in force mode and it is engine's turn.
  if (!engine.forceMode() && (engine.player() == b.toMove()))
  {
    // start clock
    engine.timing().self().start();
    // start making own move
    engine.move();
    // stop own clock ...
    engine.timing().self().stop();
    // ... and start clock of opponent
    engine.timing().opponent().start();
  }
  return true;
}

} // namespace
