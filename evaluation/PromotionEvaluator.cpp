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

#include "PromotionEvaluator.hpp"
#include "MaterialEvaluator.hpp"

namespace simplechess
{

int PromotionEvaluator::score(const Board& board) const
{
  int result = 0;

  const auto empty = Piece(Colour::none, PieceType::none);
  const int queenValue = MaterialEvaluator::pieceValue(PieceType::queen);

  // White pawns on row 7.
  const auto whitePawn = Piece(Colour::white, PieceType::pawn);
  for (char col = 'a'; col <= 'h'; ++col)
  {
    const Piece elem = board.element(toField(col, 7));
    if (elem != whitePawn)
      continue;

    // Field on row 8 must be empty.
    if (board.element(toField(col, 8)) == empty)
    {
      result += queenValue;
    }
    // ... or the field left or right to it is occupied by the opponent.
    else
    {
      const Field center = toField(col, 8);
      const Field left = leftField(center);
      const Field right = rightField(center);
      if (((left != Field::none) && (board.element(left).colour == Colour::black))
        || ((right != Field::none) && (board.element(right).colour == Colour::black)))
        result += queenValue;
    }
  } //for

  // Black pawns on row 2.
  const auto blackPawn = Piece(Colour::black, PieceType::pawn);
  for (char col = 'a'; col <= 'h'; ++col)
  {
    const Piece elem = board.element(toField(col, 2));
    if (elem != blackPawn)
      continue;

    // Field on row 1 must be empty.
    if (board.element(toField(col, 1)) == empty)
    {
      result -= queenValue;
    }
    // ... or the field left or right to it is occupied by the opponent.
    else
    {
      const Field center = toField(col, 1);
      const Field left = leftField(center);
      const Field right = rightField(center);
      if (((left != Field::none) && (board.element(left).colour == Colour::white))
        || ((right != Field::none) && (board.element(right).colour == Colour::white)))
        result -= queenValue;
    }
  } //for

  return result;
}

} //namespace
