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

#include "Convert.hpp"
#include <stdexcept>

namespace simplechess::db::mongo
{

Piece Convert::toPiece(const std::string& piece, const std::string& colour)
{
  // piece type
  PieceType pt = PieceType::none;
  if (piece == "empty")
    pt = PieceType::none;
  else if (piece == "pawn")
    pt = PieceType::pawn;
  else if (piece == "rook")
    pt = PieceType::rook;
  else if (piece == "knight")
    pt = PieceType::knight;
  else if (piece == "bishop")
    pt = PieceType::bishop;
  else if (piece == "king")
    pt = PieceType::king;
  else if (piece == "queen")
    pt = PieceType::queen;
  // not a valid string, return inacceptable piece
  else return Piece(Colour::white, PieceType::none);
  // colour
  Colour c;
  if (colour == "empty")
    c = Colour::none;
  else if (colour == "white")
    c = Colour::white;
  else if (colour == "black")
    c = Colour::black;
  // not a valid string, return inacceptable piece
  else return Piece(Colour::none, PieceType::king);

  return Piece(c, pt);
}

Field Convert::toField(const std::string& column, const int row)
{
  if ((column.size() != 1) || (row < 1) || (row > 8))
    return Field::none;
  if ((column[0] < 'a') || (column[0] > 'h'))
    return Field::none;
  return simplechess::toField(column[0], row);
}

std::string Convert::colourToMongoDbString(const Colour col)
{
  switch (col)
  {
    case Colour::none:
         return "empty";
    case Colour::white:
         return "white";
    case Colour::black:
         return "black";
    default:
         throw std::runtime_error("Invalid colour value given!");
  }
}

std::string Convert::pieceToString(const PieceType pt)
{
  switch (pt)
  {
    case PieceType::none:
         return "empty";
    case PieceType::pawn:
         return "pawn";
    case PieceType::rook:
         return "rook";
    case PieceType::knight:
         return "knight";
    case PieceType::bishop:
         return "bishop";
    case PieceType::king:
         return "king";
    case PieceType::queen:
         return "queen";
    default:
         throw std::runtime_error("Invalid piece type value given!");
  } // swi
}

} // namespace
