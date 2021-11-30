/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016, 2017, 2021  Dirk Stolle

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

#include <cstdint>
#include <iostream>

namespace simplechess
{
   /** enumeration type for players / colours */
   enum class Colour : std::uint8_t { none, white, black };

   /** enumeration type for types of pieces */
   enum class PieceType : std::uint8_t { king, queen, bishop, knight, rook, pawn, none };


   /** struct that represents a player piece */
   struct Piece
   {
     /**< colour of the piece */
     inline Colour colour() const
     {
      return static_cast<Colour>(data >> 4);
     }

     /**< type of the piece */
     inline PieceType piece() const
     {
       return static_cast<PieceType>(data & 0x0f);
     }

     /** \brief default constructor */
     Piece();

     /** \brief parameterized constructor
      *
      * \param c colour of the piece
      * \param pt type of the piece
      */
     Piece(const Colour c, const PieceType pt);


     /** \brief Checks whether the struct's content is a sensible, acceptable piece.
      *
      * \return Returns true, if the content is a sensible, acceptable piece.
      *         Returns false otherwise.
      */
     bool acceptable() const;


     /** equality operator for Piece structures
      *
      * \param other  other piece against which this piece is compared
      * \return Returns true, if both pieces are equal.
      *         Returns false otherwise.
      */
     bool operator==(const Piece& other) const;


     /** inequality operator for Piece structures
      *
      * \param other  other piece against which this piece is compared
      * \return Returns true, if both pieces are NOT equal.
      *         Returns false otherwise.
      */
     bool operator!=(const Piece& other) const;
   private:
     std::uint8_t data;
   }; //struct
} //namespace



std::ostream& operator<<(std::ostream& str, const simplechess::Colour& c);
std::ostream& operator<<(std::ostream& str, const simplechess::PieceType& pt);
std::ostream& operator<<(std::ostream& str, const simplechess::Piece& p);

#endif // SIMPLE_CHESS_PIECE_HPP
