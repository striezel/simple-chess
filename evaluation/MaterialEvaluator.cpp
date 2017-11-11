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

#include "MaterialEvaluator.hpp"

namespace simplechess
{

int MaterialEvaluator::score(const Board& board) const
{
  int result = 0;
  for (int i = static_cast<int>(Field::a1); i <= static_cast<int>(Field::h8); ++i)
  {
    const Piece elem = board.element(static_cast<Field>(i));
    if ((elem.colour == Colour::none) || (elem.piece == PieceType::none))
      continue;

    int value(0);
    switch(elem.piece)
    {
      case PieceType::none:
           continue;
           break; // not really necessary
      case PieceType::pawn:
           value = 100;
           break;
      case PieceType::bishop:
      case PieceType::knight:
           value = 300;
           break;
      case PieceType::rook:
           value = 500;
           break;
      case PieceType::queen:
           value = 900;
           break;
      // Value of king is higher than all other pieces combined, because if you
      // loose the king you loose the game.
      case PieceType::king:
           value = 1000000;
           break;
    }
    if (elem.colour == Colour::white)
      result += value;
    else
      result -= value;
  } //for
  return result;
}

} //namespace
