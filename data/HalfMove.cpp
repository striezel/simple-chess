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

#include "HalfMove.hpp"

namespace simplechess
{

HalfMove::HalfMove()
: mPiece(PieceType::none),
  mOrigin(Field::none),
  captures(false),
  mDestination(Field::none),
  mChecked(false),
  mKingsideCastling(false),
  mQueensideCastling(false)
{
}

HalfMove::HalfMove(PieceType pt, Field destination, bool capture)
: mPiece(pt),
  mOrigin(Field::none),
  captures(capture),
  mDestination(destination),
  mChecked(false),
  mKingsideCastling(false),
  mQueensideCastling(false)
{
}

HalfMove::HalfMove(PieceType pt, Field origin, Field destination, bool capture)
: mPiece(pt),
  mOrigin(origin),
  captures(capture),
  mDestination(destination),
  mChecked(false),
  mKingsideCastling(false),
  mQueensideCastling(false)
{
}

PieceType HalfMove::piece() const
{
  return mPiece;
}

Field HalfMove::origin() const
{
  return mOrigin;
}

Field HalfMove::destination() const
{
  return mDestination;
}

bool HalfMove::capture() const
{
  return captures;
}

bool HalfMove::check() const
{
  return mChecked;
}

bool HalfMove::kingsideCastling() const
{
  return mKingsideCastling;
}

bool HalfMove::queensideCastling() const
{
  return mQueensideCastling;
}

bool HalfMove::empty() const
{
  return ((mOrigin == Field::none) && (mDestination == Field::none)
      && (mPiece == PieceType::none) && !mKingsideCastling && !mQueensideCastling);
}

bool HalfMove::fromPGN(const std::string& pgn)
{
  if (pgn.empty())
    return false;
  //Is it a castling move?
  if ((pgn == "O-O") || (pgn == "O-O-O"))
  {
    mPiece = PieceType::king;
    mOrigin = Field::none;
    mDestination = Field::none;
    captures = false;
    mChecked = false;
    mKingsideCastling = (pgn == "O-O");
    mQueensideCastling = (pgn == "O-O-O");
    return true;
  }
  //Regular moves follow a certain pattern that can be expressed as regex.
  const std::regex regExPGN = std::regex("^([PRNBQK])?([a-h][1-8])?(x)?([a-h][1-8])(\\+)?$");
  std::smatch matches;
  if(!std::regex_search(pgn, matches, regExPGN))
    return false;
  //piece matched?
  if (matches[1].matched)
  {
    switch (matches.str(1).at(0))
    {
      case 'P':
           mPiece = PieceType::pawn;
           break;
      case 'R':
           mPiece = PieceType::rook;
           break;
      case 'N':
           mPiece = PieceType::knight;
           break;
      case 'B':
           mPiece = PieceType::bishop;
           break;
      case 'Q':
           mPiece = PieceType::queen;
           break;
      case 'K':
           mPiece = PieceType::king;
           break;
      default:
           return false;
    } //switch
  }
  //no letter for piece means pawn
  else
    mPiece = PieceType::pawn;

  //first field matched?
  if (matches[2].matched)
  {
    mOrigin = toField(matches.str(2).at(0), matches.str(2).at(1) - '1' + 1);
  }
  else
    mOrigin = Field::none;

  //capture?
  captures = matches[3].matched;

  //destination field matched?
  if (matches[4].matched)
  {
    mDestination = toField(matches.str(4).at(0), matches.str(4).at(1) - '1' + 1);
  }
  //there should be a destination field
  else
    return false;

  //opponent is in check now?
  mChecked = matches[5].matched;

  return true;
}

std::string HalfMove::toPGN() const
{
  //Treat special cases first.
  if (empty())
    return "";
  if (mKingsideCastling)
    return "O-O";
  if (mQueensideCastling)
    return "O-O-O";
  std::string result;
  switch (mPiece)
  {
    case PieceType::rook:
         result = "R";
         break;
    case PieceType::knight:
         result = "N";
         break;
    case PieceType::bishop:
         result = "B";
         break;
    case PieceType::queen:
         result = "Q";
         break;
    case PieceType::king:
         result = "K";
         break;
    case PieceType::pawn:
    case PieceType::none:
         //no letter for pawn
         break;
  } //switch
  if (mOrigin != Field::none)
  {
    result += std::string(1, column(mOrigin));
    result += std::string(1, '1' + row(mOrigin) - 1);
    if (!captures)
      result += "-";
  }
  if (captures)
    result += "x";
  //destination
  result += std::string(1, column(mDestination));
  result += std::string(1, '1' + row(mDestination) - 1);
  if (mChecked)
    result += "+";
  return result;
}

} //namespace
