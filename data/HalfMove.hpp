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

#ifndef SIMPLECHESS_HALFMOVE_HPP
#define SIMPLECHESS_HALFMOVE_HPP

#include "Field.hpp"
#include "Piece.hpp"

namespace simplechess
{

/** represents a half move in PGN */
class HalfMove
{
  public:
    /** default constructor */
    HalfMove();


    /** \brief constructor with values
     *
     * \param pt   type of piece that moves
     * \param destination  the destination field of the move
     * \param capture      whether a part was captured
     */
    HalfMove(PieceType pt, Field destination, bool capture);


    /** \brief constructor with values
     *
     * \param pt   type of piece that moves
     * \param origin       origin of the move
     * \param destination  the destination field of the move
     * \param capture      whether a part was captured
     */
    HalfMove(PieceType pt, Field origin, Field destination, bool capture);


    /** \brief gets the piece that moved
     *
     * \return moved piece type
     */
    PieceType piece() const;


    /** \brief gets the field of origin for the move (if known)
     *
     * \return Returns the field of origin of the move.
     */
    Field origin() const;


    /** \brief gets the destination of the move
     *
     * \return Returns the destination field of the move.
     */
    Field destination() const;


    /** \brief whether a part was captured during the move
     *
     * \return Returns true, if a part was captured during the move.
     */
    bool capture() const;
  private:
    PieceType mPiece; /**< piece that moves */
    Field mOrigin; /**< origin of the move */
    bool captures; /**< whether a piece was captured during the move */
    Field mDestination; /**< destination field of the move */
}; //class

} //namespace

#endif // SIMPLECHESS_HALFMOVE_HPP
