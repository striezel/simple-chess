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

#include "moves.hpp"
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

bool allowedPawnBlack(const Board& board, const Field from, const Field to)
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
    //It may also be an en passant move.
    return ((colDiff == 1) && (rowDiff == 1) && (board.enPassant() == to));
  }
  if (destination.colour == Colour::white)
  {
    return ((colDiff == 1) && (rowDiff == 1));
  }
  //everything else is not allowed
  return false;
}

bool allowedPawnWhite(const Board& board, const Field from, const Field to)
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
    //It may also be an en passant move.
    return ((colDiff == 1) && (rowDiff == 1) && (to == board.enPassant()));
  }
  if (destination.colour == Colour::black)
  {
    return ((colDiff == 1) && (rowDiff == 1));
  }
  //everything else is not allowed
  return false;
}

bool allowedRook(const Board& board, const Field from, const Field to)
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

bool allowedKnight(const Field from, const Field to)
{
  // Knight moves in an L-shaped step: two fields on a horizontal or vertical
  // line and one field orthogonally from that move. That is: Row and column
  // difference must be 2 and 1 (or 1 and 2).
  const int rowDiff = std::abs(row(from) - row(to));
  const int colDiff = std::abs(column(from) - column(to));
  return (((rowDiff == 1) && (colDiff == 2))
    || ((rowDiff == 2) && (colDiff == 1)));
}

bool allowedBishop(const Board& board, const Field from, const Field to)
{
  //Bishop moves diagonally, i.e. absolute difference between rows and columns
  //of start and end point must be equal and non-zero.
  const int rowDiff = std::abs(row(from) - row(to));
  const int colDiff = std::abs(column(from) - column(to));
  if ((colDiff == rowDiff) && (rowDiff != 0))
  {
    //Move is allowed, if fields between start and end are empty.
    return isEmptyStraightOrDiagonal(board, from, to);
  }
  //not allowed
  return false;
}

bool allowedQueen(const Board& board, const Field from, const Field to)
{
  //Queen can move like rook or like bishop.
  if (allowedRook(board, from, to))
    return true;
  return allowedBishop(board, from, to);
}

bool allowedKing(const Board& board, const Field from, const Field to)
{
  //King can move one field in any direction, i.e. the difference between
  //start and end point must not be more than one in any direction.
  //Only one exception is castling.

  //Check for castling.
  const bool ca = isCastlingAttemptAllowed(board, from, to);
  if (ca)
    return true;

  //regular move
  return ((std::abs(row(from) - row(to)) <= 1)
    && (std::abs(column(from) - column(to)) <= 1));
}

bool Moves::allowed(const Board& board, const Field from, const Field to)
{
  //If start and destination are equal, it's not a valid move.
  if (from == to)
    return false;
  if ((from == Field::none) || (to == Field::none))
    return false;
  const Piece & start = board.element(from);
  //If the field is empty, it is no valid start point.
  if (start.piece == PieceType::none)
    return false;
  const Piece & destination = board.element(to);
  //If there is a piece of the same colour on the destination field, then the
  // move is not allowed.
  if (start.colour == destination.colour)
    return false;

  switch(start.piece)
  {
    case PieceType::pawn:
         if (start.colour == Colour::white)
           return allowedPawnWhite(board, from, to);
         //Must be a black pawn then.
         return allowedPawnBlack(board, from, to);
    case PieceType::rook:
         return allowedRook(board, from, to);
    case PieceType::knight:
         return allowedKnight(from, to);
    case PieceType::bishop:
         return allowedBishop(board, from, to);
    case PieceType::queen:
         return allowedQueen(board, from, to);
    case PieceType::king:
         return allowedKing(board, from, to);
    case PieceType::none:
         //will never happen
         return false;
  } //switch
  throw std::range_error("Piece type is out of range!");
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
  } //switch
}

} //namespace