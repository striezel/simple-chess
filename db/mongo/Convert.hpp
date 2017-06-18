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

#ifndef SIMPLECHESS_DB_MONGO_CONVERT_HPP
#define SIMPLECHESS_DB_MONGO_CONVERT_HPP

#include <string>
#include "../../data/Field.hpp"
#include "../../data/Piece.hpp"

namespace simplechess
{

namespace db
{

namespace mongo
{

/** class that handles conversion between MongoDB values and C++ values */
class Convert
{
  public:
    /** \brief converts a pair of piece and colour strings from MongoDB to the corresponding piece class
     *
     * \param piece  the piece value from MongoDB
     * \param colour the colour value from MongoDB
     * \return Returns a corresponding piece instance.
     *         If the given piece-colour combination is invalid, then the
     *         returned Piece's acceptable() method will return false.
     */
    static Piece toPiece(const std::string& piece, const std::string& colour);


    /** \brief converts a column row pair from MongoDB to the corresponding field
     *
     * \param column  the column (e.g. "a", "b", "c", etc.)
     * \param row     the row number (from [1;8])
     * \return Returns the corresponding field, if parameters are valid.
     *         Returns Field::none, if one of the parameters is invalid.
     */
    static Field toField(const std::string& column, const int row);


    /** \brief converts a colour value to the corresponding string for MongoDB
     *
     * \param col  the colour, must not be Colour::none
     * \return Returns the string representation of the colour.
     */
    static std::string colourToMongoDbString(const Colour col);


    /** \brief translates a boolean to the corresponding string representation
     *
     * \param b   a boolean value
     * \return Returns "true", if b is true. Returns "false" otherwise.
     */
    static std::string boolToMongoDbString(const bool b);


    /** \brief translates a piece type to the corresponding MongoDB string
     *
     * \param pt   the piece type
     * \return Returns a string representing the piece type for MongoDB.
     */
    static std::string pieceToString(const PieceType pt);
}; //class

} //namespace

} //namespace

} //namespace

#endif // SIMPLECHESS_DB_MONGO_CONVERT_HPP
