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

#include "piece.hpp"

namespace simplechess
{

Piece::Piece()
: colour(Colour::none),
  piece(PieceType::none)
{
}

Piece::Piece(Colour c, PieceType pt)
: colour(c),
  piece(pt)
{
}

bool Piece::operator==(const Piece& other) const
{
  return ((colour == other.colour) && (piece == other.piece));
}

} //namespace
