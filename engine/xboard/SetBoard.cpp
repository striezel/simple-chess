/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2018, 2021  Dirk Stolle

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

#include "SetBoard.hpp"
#include "../Engine.hpp"
#include "../io-utils.hpp"
#include "../../libsimple-chess/data/Board.hpp"

namespace simplechess::xboard
{

SetBoard::SetBoard(const std::string& fen)
: mFEN(fen)
{
}

bool SetBoard::process()
{
  Board board;
  if (!board.fromFEN(mFEN))
  {
    // Ill-formed FEN string.
    sendCommand("tellusererror Illegal position");
    sendCommand("Error (illegal position): setboard " + mFEN);
    return true;
  }
  Engine::get().board() = board;
  return true;
}

} // namespace
