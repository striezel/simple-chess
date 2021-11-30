/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016, 2018, 2021  Dirk Stolle

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
#include "Moves.hpp"

namespace simplechess
{

bool isUnderAttack(const Board& board, const Colour by, const Field field)
{
  Board boardCopy(board);
  boardCopy.setToMove(by);
  for(int i = static_cast<int>(Field::a1); i <= static_cast<int>(Field::h8); ++i)
  {
    const Piece& piece = board.element(static_cast<Field>(i));
    if (piece.colour() == by)
    {
      if (Moves::isAllowedPattern(boardCopy, static_cast<Field>(i), field))
        return true;
    }
  } // for
  return false;
}

bool isInCheck(const Board& board, const Colour colour)
{
  for(int i = static_cast<int>(Field::a1); i <= static_cast<int>(Field::h8); ++i)
  {
    const Piece& piece = board.element(static_cast<Field>(i));
    if ((piece.piece() == PieceType::king) && (piece.colour() == colour))
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
             // invalid argument, so just return false
             return false;
      } // switch
      return isUnderAttack(board, opponent, static_cast<Field>(i));
    } // if
  } // for
  // No king found.
  return false;
}

bool isCheckMate(const Board& board, const Colour colour)
{
  // Player can only be checkmated, if he/she is in check, too.
  if (!board.isInCheck(colour))
    return false;
  // If player is not the one to move, (s)he shouldn't be in checkmate, because
  // checkmate can only occur after a move made by the opponent.
  if (board.toMove() != colour)
    return false;

  // The basic idea here is to check for all possible moves and check whether
  // one of the moves leads to a position where the player is not in check any
  // more.
  for(int i = static_cast<int>(Field::a1); i <= static_cast<int>(Field::h8); ++i)
  {
    const Piece& piece = board.element(static_cast<Field>(i));
    if (piece.colour() == colour)
    {
      for(int j = static_cast<int>(Field::a1); j <= static_cast<int>(Field::h8); ++j)
      {
        Board newBoard = board;
        if (newBoard.move(static_cast<Field>(i), static_cast<Field>(j), PieceType::queen))
        {
          // Move was possible. Are we not in check any more?
          // If so, then this is no checkmate.
          if (!newBoard.isInCheck(colour))
            return false;
        } // if
      } // for all fields (j)
    } // if colour
  } // for all fields (i)
  // No move out of check found. Player is checkmate.
  return true;
}

} // namespace
