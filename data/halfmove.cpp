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

#include "halfmove.hpp"

namespace simplechess
{

HalfMove::HalfMove()
: mPiece(PieceType::none),
  mOrigin(Field::none),
  captures(false),
  mDestination(Field::none)
{
}

HalfMove::HalfMove(PieceType pt, Field destination, bool capture)
: mPiece(pt),
  mOrigin(Field::none),
  captures(capture),
  mDestination(destination)
{
}

HalfMove::HalfMove(PieceType pt, Field origin, Field destination, bool capture)
: mPiece(pt),
  mOrigin(origin),
  captures(capture),
  mDestination(destination)
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

} //namespace
