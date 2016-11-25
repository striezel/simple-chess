/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016  Dirk Stolle

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

#include "check.hpp"
#include "moves.hpp"

namespace simplechess
{

bool isUnderAttack(const Board& board, const Colour by, const Field field)
{
  for(int i = static_cast<int>(Field::a1); i <= static_cast<int>(Field::h8); ++i)
  {
    const Piece& piece = board.element(static_cast<Field>(i));
    if (piece.colour == by)
    {
      if (Moves::allowed(board, static_cast<Field>(i), field))
        return true;
    }
  } //for
  return false;
}

bool isInCheck(const Board& board, const Colour colour)
{
  for(int i = static_cast<int>(Field::a1); i <= static_cast<int>(Field::h8); ++i)
  {
    const Piece& piece = board.element(static_cast<Field>(i));
    if ((piece.piece == PieceType::king) && (piece.colour == colour))
    {
      Colour opponent = Colour::none;
      switch(colour)
      {
        case Colour::black:
             opponent = Colour::white;
             break;
        case Colour::white:
             opponent = Colour::black;
             break;
        case Colour::none:
             //invalid argument, so just return false
             return false;
      } //switch
      return isUnderAttack(board, opponent, static_cast<Field>(i));
    } //if
  } //for
  //No king found.
  return false;
}

} //namespace
