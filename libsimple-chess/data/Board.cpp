/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016, 2017, 2018, 2021  Dirk Stolle

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

#include "Board.hpp"
#include <cmath>
#include <unordered_map>
#include "../rules/check.hpp"
#include "../rules/Moves.hpp"
#include "../../util/strings.hpp"

namespace simplechess
{

/** \brief Returns the next column for a given column.
 *
 * \param character that denotes the current column
 * \return Returns the character for the next column.
 *         If the given column is out of range, the function will return 'a'.
 */
char nextColumn(const char column)
{
  char nextCol = static_cast<char>(column + 1);
  if ((nextCol > 'h') || (nextCol < 'a'))
  {
    nextCol = 'a';
  }
  return nextCol;
}


Board::Board()
: mFields(std::array<Piece, 64>()),
  mToMove(Colour::white),
  mEnPassant(Field::none),
  mCastling(Castling()),
  mHalfmoves50(0),
  mBlackInCheck(false),
  mWhiteInCheck(false)
{
  for(int i = static_cast<int>(Field::a1); i <= static_cast<int>(Field::h8); ++i)
  {
    mFields[i] = Piece();
  }
}

const Piece& Board::element(const Field f) const
{
  switch (f)
  {
    case Field::none:
         throw std::runtime_error("Field does not exist on board!");
    default:
         return mFields[static_cast<int>(f)];
  }
}

const Colour& Board::toMove() const
{
  return mToMove;
}

const Field& Board::enPassant() const
{
  return mEnPassant;
}

const Castling& Board::castling() const
{
  return mCastling;
}

unsigned int Board::halfmovesFifty() const
{
  return mHalfmoves50;
}

bool Board::setElement(const Field field, const Piece& piece)
{
  if ((field == Field::none) || !piece.acceptable())
    return false;
  // set element
  mFields[static_cast<int>(field)] = piece;
  return true;
}

bool Board::setToMove(const Colour who)
{
  if (who == Colour::none)
    return false;
  // set player that is to move
  mToMove = who;
  return true;
}

bool Board::setEnPassant(const Field ep)
{
  // Allowed values are none for "no e.p." or any field on 3rd or 6th row.
  if ((ep == Field::none) || (row(ep) == 3) || (row(ep) == 6))
  {
    mEnPassant = ep;
    return true;
  }
  // invalid field given
  return false;
}

void Board::setCastling(const Castling& castlingInfo)
{
  mCastling = castlingInfo;
}

void Board::setHalfmovesFifty(const unsigned int halfmoves50)
{
  mHalfmoves50 = halfmoves50;
}

bool Board::isInCheck(const Colour colour) const
{
  switch(colour)
  {
    case Colour::white:
         return mWhiteInCheck;
    case Colour::black:
         return mBlackInCheck;
    default:
         // "None" can never be in check.
         return false;
  } // switch
}

void Board::updateCheckCache()
{
  // update info who is in check
  mWhiteInCheck = simplechess::isInCheck(*this, Colour::white);
  mBlackInCheck = simplechess::isInCheck(*this, Colour::black);
}

bool Board::fromFEN(const std::string& FEN)
{
  // split into single parts
  const std::vector<std::string> parts = util::split(FEN, ' ');
  if (parts.empty())
    return false;
  // first part: pieces on board
  const std::unordered_map<char, Piece> fenmap = {
    { 'r', Piece(Colour::black, PieceType::rook)},
    { 'n', Piece(Colour::black, PieceType::knight)},
    { 'b', Piece(Colour::black, PieceType::bishop)},
    { 'q', Piece(Colour::black, PieceType::queen)},
    { 'k', Piece(Colour::black, PieceType::king)},
    { 'p', Piece(Colour::black, PieceType::pawn)},

    { 'R', Piece(Colour::white, PieceType::rook)},
    { 'N', Piece(Colour::white, PieceType::knight)},
    { 'B', Piece(Colour::white, PieceType::bishop)},
    { 'Q', Piece(Colour::white, PieceType::queen)},
    { 'K', Piece(Colour::white, PieceType::king)},
    { 'P', Piece(Colour::white, PieceType::pawn)}
  };

  const std::vector<std::string> rows = util::split(parts[0], '/');
  if (rows.size() != 8)
    return false;
  int boardRow = 8;
  for(const std::string& singleRow : rows)
  {
    char boardColumn = 'a';
    for (unsigned int j = 0; j < singleRow.size(); ++j)
    {
      const auto iter = fenmap.find(singleRow[j]);
      if (iter != fenmap.end())
      {
        mFields[static_cast<int>(toField(boardColumn, boardRow))] = iter->second;
        boardColumn = nextColumn(boardColumn);
      } // if
      else if ((singleRow[j] >= '1') && (singleRow[j] <= '8'))
      {
        const auto count = singleRow[j] - '1' + 1;
        for (int k = 1; k <= count; ++k)
        {
          mFields[static_cast<int>(toField(boardColumn, boardRow))] = Piece(Colour::none, PieceType::none);
          boardColumn = nextColumn(boardColumn);
        }
      } // else if '1'..'8'
      else
      {
        // invalid character
        return false;
      }
    } // for j
    boardRow = boardRow - 1;
  } // for singleRow

  // Who is to move?
  if (parts.size() > 1)
  {
    if (parts[1] == "b")
      mToMove = Colour::black;
    else
      mToMove = Colour::white;
  }
  else
    mToMove = Colour::white;

  // Info about castling?
  if (parts.size() > 2)
  {
    mCastling.fromFEN(parts[2]);
  }
  else
  {
    mCastling = Castling();
    // No information is given, so let's guess as good as possible from current
    // position.
    if (element(Field::e1) == Piece(Colour::white, PieceType::king))
    {
      mCastling.white_kingside = element(Field::h1) == Piece(Colour::white, PieceType::rook);
      mCastling.white_queenside = element(Field::a1) == Piece(Colour::white, PieceType::rook);
    }
    else
    {
      mCastling.white_kingside = false;
      mCastling.white_queenside = false;
    }
    mCastling.white_castled = (mCastling.white_kingside || mCastling.white_queenside) ? Ternary::false_value : Ternary::maybe_value;
    if (element(Field::e8) == Piece(Colour::black, PieceType::king))
    {
      mCastling.black_kingside = element(Field::h8) == Piece(Colour::black, PieceType::rook);
      mCastling.black_queenside = element(Field::a8) == Piece(Colour::black, PieceType::rook);
    }
    else
    {
      mCastling.black_kingside = false;
      mCastling.black_queenside = false;
    }
    mCastling.black_castled = (mCastling.black_kingside || mCastling.black_queenside) ? Ternary::false_value : Ternary::maybe_value;
  } // castling

  // Parse info about en passant move.
  if (parts.size() > 3)
  {
    if (parts[3] == "-")
    {
      mEnPassant = Field::none;
    }
    else
    {
      try
      {
        mEnPassant = toField(parts[3].at(0), parts[3].at(1) - '1' + 1);
        if ((row(mEnPassant) != 3) && (row(mEnPassant) != 6))
          return false;
      }
      catch(...)
      {
        return false;
      }
    } // else
  } // if
  else
    mEnPassant = Field::none;

  // Half moves since last capture or pawn move.
  if (parts.size() > 4)
  {
    int val = -1;
    if (!util::stringToInt(parts[4], val) || (val < 0))
      return false;
    mHalfmoves50 = val;
  }
  else
    // No information, so let's start with zero here.
    mHalfmoves50 = 0;

  // update info who is in check
  updateCheckCache();

  // Other info from FEN is not parsed yet, so return true for now.
  return true;
}

bool Board::move(const Field from, const Field to, PieceType promoteTo, const bool onlyAllowed)
{
  if ((from == Field::none) || (to == Field::none))
    return false;

  const Piece start = element(from);
  // Is the correct player moving?
  if (toMove() != start.colour())
  {
    return false;
  }

  // Check whether the move is allowed.
  const bool allow = onlyAllowed ?
      // If only allowed moves shall be performed, do the full check.
      Moves::isAllowed(*this, from, to)
      // Otherwise just do whatever the move is.
      : true;
  if (!allow)
    return false;
  // save for possible later use
  const Piece dest = element(to);

  // Handle counter for fifty move rule.
  if ((start.piece() == PieceType::pawn) || (dest.piece() != PieceType::none))
  {
    // Pawn has been moved or piece will be captured: reset counter.
    mHalfmoves50 = 0;
  }
  else
  {
    // No pawn move or capture, increase counter.
    ++mHalfmoves50;
  }

  // Move is allowed.
  // -- "copy" piece to destination field
  mFields[static_cast<int>(to)] = start;
  // -- remove piece in start field
  mFields[static_cast<int>(from)] = Piece(Colour::none, PieceType::none);
  // holds en passant data for next move
  Field enPassantData = Field::none;
  // -- check for special moves of pawn pieces
  if (start.piece() == PieceType::pawn)
  {
    // check for promotion
    // -- sanitize promotion piece
    Moves::sanitizePromotion(promoteTo);
    // -- check for promotion of white pawn
    if ((start.colour() == Colour::white) && (row(to) == 8))
    {
      mFields[static_cast<int>(to)] = Piece(Colour::white, promoteTo);
    }
    // -- check for promotion of black pawn
    else if ((start.colour() == Colour::black) && (row(to) == 1))
    {
       mFields[static_cast<int>(to)] = Piece(Colour::black, promoteTo);
    }
    // check for en passant capture
    else if (to == enPassant())
    {
      const int colDiff = std::abs(column(from) - column(to));
      const int rowDiff = std::abs(row(to) - row(from));
      if ((colDiff == 1) && (rowDiff == 1))
      {
        // remove captured pawn
        int removeRow = row(to);
        if (removeRow == 3)
          removeRow = 4;
        else
          removeRow = 5;
        mFields[static_cast<int>(toField(column(to), removeRow))] = Piece(Colour::none, PieceType::none);
      } // if
    } // if en passant field is destination
    // check whether en passant capture is possible in next move
    if ((start.colour() == Colour::white) && (row(from) == 2) && (row(to) == 4))
      enPassantData = toField(column(from), 3);
    else if ((start.colour() == Colour::black) && (row(from) == 7) && (row(to) == 5))
      enPassantData = toField(column(from), 6);
  }// if pawn
  // -- check for castling move
  if (start.piece() == PieceType::king)
  {
    if ((start.colour() == Colour::white) && (from == Field::e1))
    {
      if ((to == Field::c1) && (dest.piece() == PieceType::none))
      {
        // white queenside castling
        // King was already moved, we just have to move the rook here.
        mFields[static_cast<int>(Field::a1)] = Piece(Colour::none, PieceType::none);
        mFields[static_cast<int>(Field::d1)] = Piece(Colour::white, PieceType::rook);
        mCastling.white_castled = Ternary::true_value;
      }
      if ((to == Field::g1) && (dest.piece() == PieceType::none))
      {
        // white kingside castling
        // King was already moved, we just have to move the rook here.
        mFields[static_cast<int>(Field::h1)] = Piece(Colour::none, PieceType::none);
        mFields[static_cast<int>(Field::f1)] = Piece(Colour::white, PieceType::rook);
        mCastling.white_castled = Ternary::true_value;
      }
    } // if white king at initial position
    else if ((start.colour() == Colour::black) && (from == Field::e8))
    {
      if ((to == Field::c8) && (dest.piece() == PieceType::none))
      {
        // black queenside castling
        // King was already moved, we just have to move the rook here.
        mFields[static_cast<int>(Field::a8)] = Piece(Colour::none, PieceType::none);
        mFields[static_cast<int>(Field::d8)] = Piece(Colour::black, PieceType::rook);
        mCastling.black_castled = Ternary::true_value;
      }
      if ((to == Field::g8) && (dest.piece() == PieceType::none))
      {
        // black kingside castling
        // King was already moved, we just have to move the rook here.
        mFields[static_cast<int>(Field::h8)] = Piece(Colour::none, PieceType::none);
        mFields[static_cast<int>(Field::f8)] = Piece(Colour::black, PieceType::rook);
        mCastling.black_castled = Ternary::true_value;
      }
    }// if black king at initial position
  } // if king may be castling
  // -- castling update
  if (start.piece() == PieceType::king)
  {
    if (start.colour() == Colour::black)
    {
      mCastling.black_kingside = false;
      mCastling.black_queenside = false;
    }
    else
    {
      mCastling.white_kingside = false;
      mCastling.white_queenside = false;
    }
  } // if king
  else if (start.piece() == PieceType::rook)
  {
    if (start.colour() == Colour::black)
    {
      if (from == Field::a8)
        mCastling.black_queenside = false;
      else if (from == Field::h8)
        mCastling.black_kingside = false;
    } // if black rook moved
    else if (start.colour() == Colour::white)
    {
      if (from == Field::a1)
        mCastling.white_queenside = false;
      else if (from == Field::h1)
        mCastling.white_kingside = false;
    } // if white rook moved
  } // if rook
  // -- update en passant data
  mEnPassant = enPassantData;
  // -- determine whether anyone is in check
  const bool whiteCheck = simplechess::isInCheck(*this, Colour::white);
  mWhiteInCheck = whiteCheck;
  const bool blackCheck = simplechess::isInCheck(*this, Colour::black);
  mBlackInCheck = blackCheck;
  // TODO: check for checkmate
  // -- update colour that is to move
  if (mToMove == Colour::white)
    mToMove = Colour::black;
  else
    mToMove = Colour::white;
  return true;
}

Field Board::findNext(const Piece& piece, Field start) const
{
  if (start == Field::none)
    start = Field::a1;
  for(int i = static_cast<int>(start); i <= static_cast<int>(Field::h8); ++i)
  {
    if (element(static_cast<Field>(i)) == piece)
      return static_cast<Field>(i);
  } // for
  return Field::none;
}

} // namespace
