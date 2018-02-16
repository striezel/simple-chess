/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016, 2017, 2018  Dirk Stolle

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

#ifndef SIMPLE_CHESS_CASTLING_HPP
#define SIMPLE_CHESS_CASTLING_HPP

#include <string>
#include "Ternary.hpp"

namespace simplechess
{

/** \brief structure to hold castling information, i.e. which player can still
           perform castling on which side
 */
struct Castling
{
  bool white_kingside; /**< whether kingside castling for white is still possible */
  bool white_queenside; /**< whether queenside castling for white is still possible */
  Ternary white_castled; /**< whether the white player has performed castling */
  bool black_kingside; /**< whether kingside castling for black is still possible */
  bool black_queenside; /**< whether queenside castling for black is still possible */
  Ternary black_castled; /**< whether the black player has performed castling */

  /** \brief Default constructor. */
  Castling();

  /** \brief Provides Forsyth-Edwards notation of the castling information.
   *
   * \return Returns a string like "-", "KQkq", or similar that reflects the
   * castling options that are still possible.
   */
  std::string toFEN() const;

  /** \brief Initializes the struct from a Forsyth-Edwards notation of the castling information. */
  void fromFEN(const std::string& FEN);
}; // struct

} // namespace

#endif // SIMPLE_CHESS_CASTLING_HPP
