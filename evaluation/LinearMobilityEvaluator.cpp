/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2018  Dirk Stolle

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

#include "LinearMobilityEvaluator.hpp"
#include "../rules/Moves.hpp"

namespace simplechess
{

// score ten centipawns per move
const int LinearMobilityEvaluator::centipawnsPerMove = 10;

int LinearMobilityEvaluator::score(const Board& board) const
{
  Board moveBoard(board);
  int result = 0;
  for (int i = static_cast<int>(Field::a1); i <= static_cast<int>(Field::h8); ++i)
  {
    const Piece elem = board.element(static_cast<Field>(i));
    if ((elem.colour == Colour::none) || (elem.piece == PieceType::none))
      continue;

    // Set current colour as the player who is to move. Otherwise moves will
    // not be allowed.
    moveBoard.setToMove(elem.colour);

    for (int j = static_cast<int>(Field::a1); j <= static_cast<int>(Field::h8); ++j)
    {
      if (Moves::isAllowed(moveBoard, static_cast<Field>(i), static_cast<Field>(j)))
      {
        if (elem.colour == Colour::white)
          result += centipawnsPerMove;
        else
          result -= centipawnsPerMove;
      } // if move is allowed
    } // for j
  } // for i
  return result;
}

} // namespace
