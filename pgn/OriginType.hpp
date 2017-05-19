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

#ifndef SIMPLECHESS_PGN_ORIGINTYPE_HPP
#define SIMPLECHESS_PGN_ORIGINTYPE_HPP

namespace simplechess
{

namespace pgn
{

/** \brief enumeration type to determine the status of the origin field in PGN move
 */
enum class OriginType
{
  none, /**< no field of origin is set */

  file, /**< only letter a to h is set */

  rank, /**< only number 1 to 8 is set */

  full /**< complete field is given */
};

}

} //namespace

#endif // SIMPLECHESS_PGN_ORIGINTYPE_HPP
