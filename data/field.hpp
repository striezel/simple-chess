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

#ifndef SIMPLE_CHESS_FIELD_HPP
#define SIMPLE_CHESS_FIELD_HPP

namespace simplechess
{
  //enumeration type for fields on chess board
  enum class Field {
      a1, a2, a3, a4, a5, a6, a7, a8,
      b1, b2, b3, b4, b5, b6, b7, b8,
      c1, c2, c3, c4, c5, c6, c7, c8,
      d1, d2, d3, d4, d5, d6, d7, d8,
      e1, e2, e3, e4, e5, e6, e7, e8,
      f1, f2, f3, f4, f5, f6, f7, f8,
      g1, g2, g3, g4, g5, g6, g7, g8,
      h1, h2, h3, h4, h5, h6, h7, h8
   };


   /* returns the column of a given field */
   char column(Field f);


   /* returns the row of a given field */
   int row(Field f);
} //namespace

#endif // SIMPLE_CHESS_FIELD_HPP
