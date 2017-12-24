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

#include "Usermove.hpp"
#include <sstream>
#include "../io-utils.hpp"
#include "../Engine.hpp"
#include "../../rules/Moves.hpp"

namespace simplechess
{

Usermove::Usermove(const Field ori, const Field dest, const PieceType promo)
: origin(ori),
  destination(dest),
  promoteTo(promo)
{
}

bool Usermove::process()
{
  Board& b = Engine::get().board();
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
  // Make own move, but only if not in force mode and it is engine's turn.
  if (!Engine::get().forceMode() && (Engine::get().player() == b.toMove()))
  {
    // start clock
    Engine::get().timing().self().start();
    // start making own move
    Engine::get().move();
    Engine::get().timing().self().stop();
  }
  return true;
}

} // namespace
