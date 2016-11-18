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

#ifndef SIMPLE_CHESS_PIECE_HPP
#define SIMPLE_CHESS_PIECE_HPP

namespace simplechess
{
   //enumeration type for players / colours
   enum Colour { none, white, black };

   //enumeration type for types of pieces
   enum class PieceType { none, king, queen, bishop, knight, rook, pawn};

   struct Piece
   {
     Colour colour;
     PieceType piece;

     /* default constructor */
     Piece();

     /* parametrized constructor */
     Piece(Colour c, PieceType pt);

     /* equality operator for Piece structures */
     bool operator==(const Piece& other) const;
   }; //struct
} //namespace

#endif // SIMPLE_CHESS_PIECE_HPP
