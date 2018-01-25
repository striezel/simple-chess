/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016, 2017, 2018  Dirk Stolle

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

#include "Moves.hpp"
#include <cmath>

namespace simplechess
{

int signum(const int val)
{
  return (0 < val) - (val < 0);
}

bool isEmptyStraightOrDiagonal(const Board& board, const Field from, const Field to)
{
  const int rowDiff = row(to) - row(from);
  const int colDiff = column(to) - column(from);

  int curRow = row(from) + signum(rowDiff);
  int curCol = column(from) + signum(colDiff);
  while ((curRow != row(to)) || (curCol != column(to)))
  {
    //check if field at current "coordinates" is empty - if not, return
    if (board.element(toField(curCol, curRow)).piece != PieceType::none)
      return false;
    //move to next field
    curRow = curRow + signum(rowDiff);
    curCol = curCol + signum(colDiff);
  } //while
  //All fields empty, all OK.
  return true;
}

bool isCastlingAttemptAllowed(const Board& board, const Field from, const Field to)
{
  const Piece & start = board.element(from);
  const Piece & dest = board.element(to);
  if ((start.colour == Colour::white) && (from == Field::e1))
  {
    if ((to == Field::c1) && (dest.piece == PieceType::none))
    {
      //fields b1, c1 and d1 must be empty
      bool empty = (board.element(Field::b1).piece == PieceType::none)
        && (board.element(Field::c1).piece == PieceType::none)
        && (board.element(Field::d1).piece == PieceType::none);
      return (empty && board.castling().white_queenside);
    }
    if ((to == Field::g1) && (dest.piece == PieceType::none))
    {
      //fields f1 and g1 must be empty
      return ((board.element(Field::f1).piece == PieceType::none)
        && (board.element(Field::g1).piece == PieceType::none)
      //... and castling still must be possible
        && board.castling().white_kingside);
    }
  } //if white king at initial position
  else if ((start.colour == Colour::black) && (from == Field::e8))
  {
    if ((to == Field::c8) && (dest.piece == PieceType::none))
    {
      //fields b8, c8 and d8 must be empty
      bool empty = (board.element(Field::b8).piece == PieceType::none)
        && (board.element(Field::c8).piece == PieceType::none)
        && (board.element(Field::d8).piece == PieceType::none);
      return (empty && board.castling().black_queenside);
    }
    if ((to == Field::g8) && (dest.piece == PieceType::none))
    {
      //fields f8 and g8 must be empty
      return ((board.element(Field::f8).piece == PieceType::none)
        && (board.element(Field::g8).piece == PieceType::none)
      // ... and castling still must be possible
        && board.castling().black_kingside);
    }
  } //if black king at initial position
  return false;
}

bool allowedPatternPawnBlack(const Board& board, const Field from, const Field to)
{
  const int rowDiff = row(from) - row(to);
  const int colDiff = std::abs(column(from) - column(to));
  //If dest. is empty, move may only be one step ahead; or two if in initial position.
  const Piece & destination = board.element(to);
  if (destination.colour == Colour::none)
  {
    const auto & field3 = board.element(toField(column(from), 6));
    if ((colDiff == 0) && ((rowDiff == 1) || ((rowDiff == 2) && (row(from) == 7) && (field3.piece == PieceType::none))))
      return true;
    // It may also be an en passant move.
    return ((colDiff == 1) && (rowDiff == 1) && (board.enPassant() == to));
  }
  if (destination.colour == Colour::white)
  {
    return ((colDiff == 1) && (rowDiff == 1));
  }
  // Everything else is not allowed.
  return false;
}

bool allowedPatternPawnWhite(const Board& board, const Field from, const Field to)
{
  const int rowDiff = row(to) - row(from);
  const int colDiff = std::abs(column(from) - column(to));
  //If dest. is empty, move may only be one step ahead; or two if in initial position.
  const Piece & destination = board.element(to);
  if (destination.colour == Colour::none)
  {
    const auto & field3 = board.element(toField(column(from), 3));
    if ((colDiff == 0) && ((rowDiff == 1) || ((rowDiff == 2) && (row(from) == 2) && (field3.colour == Colour::none))))
      return true;
    // It may also be an en passant move.
    return ((colDiff == 1) && (rowDiff == 1) && (to == board.enPassant()));
  }
  if (destination.colour == Colour::black)
  {
    return ((colDiff == 1) && (rowDiff == 1));
  }
  // Everything else is not allowed.
  return false;
}

bool allowedPatternRook(const Board& board, const Field from, const Field to)
{
  //Rook moves horizontally or vertically only, i.e. either column or row
  //must be identical.
  if ((column(from) == column(to)) || (row(from) == row(to)))
  {
    //Move is allowed, if fields between start and end are empty.
    return isEmptyStraightOrDiagonal(board, from, to);
  }
  //Does not match the rook move pattern, therefor not allowed.
  return false;
}

bool allowedPatternKnight(const Field from, const Field to)
{
  // Knight moves in an L-shaped step: two fields on a horizontal or vertical
  // line and one field orthogonally from that move. That is: Row and column
  // difference must be 2 and 1 (or 1 and 2).
  const int rowDiff = std::abs(row(from) - row(to));
  const int colDiff = std::abs(column(from) - column(to));
  return (((rowDiff == 1) && (colDiff == 2))
    || ((rowDiff == 2) && (colDiff == 1)));
}

bool allowedPatternBishop(const Board& board, const Field from, const Field to)
{
  // Bishop moves diagonally, i.e. absolute difference between rows and columns
  // of start and end point must be equal and non-zero.
  const int rowDiff = std::abs(row(from) - row(to));
  const int colDiff = std::abs(column(from) - column(to));
  if ((colDiff == rowDiff) && (rowDiff != 0))
  {
    // Move is allowed, if fields between start and end are empty.
    return isEmptyStraightOrDiagonal(board, from, to);
  }
  // not allowed
  return false;
}

bool allowedPatternQueen(const Board& board, const Field from, const Field to)
{
  // Queen can move like rook or like bishop.
  if (allowedPatternRook(board, from, to))
    return true;
  return allowedPatternBishop(board, from, to);
}

bool allowedPatternKing(const Board& board, const Field from, const Field to)
{
  // King can move one field in any direction, i.e. the difference between
  // start and end point must not be more than one in any direction.
  // Only one exception is castling.

  // Check for castling.
  const bool ca = isCastlingAttemptAllowed(board, from, to);
  if (ca)
    return true;

  // regular move
  return ((std::abs(row(from) - row(to)) <= 1)
    && (std::abs(column(from) - column(to)) <= 1));
}

bool Moves::isAllowed(const Board& board, const Field from, const Field to)
{
  const bool ok = isAllowedPattern(board, from, to);
  // If the move itself is not legal so far, then return it.
  if (!ok)
    return false;
  // Check whether player puts himself/herself into check after move.
  Board b2(board);
  if (!b2.move(from, to, PieceType::queen, false))
    return false;
  // Move is only allowed, if the original player did not move himself/herself
  // into check.
  return !b2.isInCheck(board.toMove());
}

bool Moves::isAllowedPattern(const Board& board, const Field from, const Field to)
{
  // If start and destination are equal, it's not a valid move.
  if (from == to)
    return false;
  // None is neither a valid origin nor a valid destination.
  if ((from == Field::none) || (to == Field::none))
    return false;
  const Piece & start = board.element(from);
  // If the field is empty, it is no valid start point.
  if (start.piece == PieceType::none)
    return false;
  const Piece & destination = board.element(to);
  // If there is a piece of the same colour on the destination field, then the
  // move is not allowed.
  if (start.colour == destination.colour)
    return false;

  switch(start.piece)
  {
    case PieceType::pawn:
         if (start.colour == Colour::white)
           return allowedPatternPawnWhite(board, from, to);
         //Must be a black pawn then.
         else
           return allowedPatternPawnBlack(board, from, to);
    case PieceType::rook:
         return allowedPatternRook(board, from, to);
    case PieceType::knight:
         return allowedPatternKnight(from, to);
    case PieceType::bishop:
         return allowedPatternBishop(board, from, to);
    case PieceType::queen:
         return allowedPatternQueen(board, from, to);
    case PieceType::king:
         return allowedPatternKing(board, from, to);
    case PieceType::none:
         // This will never happen.
         return false;
    default:
         // Will never happen either, unless someone adds new pieces.
         throw std::range_error("Piece type is out of range!");
  } // switch
}

void Moves::sanitizePromotion(PieceType& promoteTo)
{
  switch(promoteTo)
  {
    case PieceType::queen:
    case PieceType::knight:
    case PieceType::bishop:
    case PieceType::rook:
         return;
    default:
         //Some other piece - change to queen.
         promoteTo = PieceType::queen;
         break;
  } // switch
}

bool Moves::isPromotion(const Board& board, const Field from, const Field to)
{
  if (to == Field::none)
  {
    return false;
  }
  return ((board.element(from) == Piece(Colour::white, PieceType::pawn)) && (row(to) == 8))
  || ((board.element(from) == Piece(Colour::black, PieceType::pawn)) && (row(to) == 1));
}

bool Moves::performMove(Board& board, const Field from, const Field to, PieceType promoteTo)
{
  return board.move(from, to, promoteTo);
}

} // namespace
