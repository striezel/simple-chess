/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016, 2017, 2018, 2021, 2022  Dirk Stolle

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

#include <cstdint>
#include <stdexcept>

namespace simplechess
{
  /** enumeration type for fields on chess board */
  enum class Field : std::uint8_t {
      a1, a2, a3, a4, a5, a6, a7, a8,
      b1, b2, b3, b4, b5, b6, b7, b8,
      c1, c2, c3, c4, c5, c6, c7, c8,
      d1, d2, d3, d4, d5, d6, d7, d8,
      e1, e2, e3, e4, e5, e6, e7, e8,
      f1, f2, f3, f4, f5, f6, f7, f8,
      g1, g2, g3, g4, g5, g6, g7, g8,
      h1, h2, h3, h4, h5, h6, h7, h8,
      none
  };


  /** \brief Gets the column/file of a given field.
   *
   * \param  f a field, must not be none
   * \return Returns the column/file of the given field.
   */
  constexpr char column(const Field f)
  {
    switch (f)
    {
      case Field::a1:
      case Field::a2:
      case Field::a3:
      case Field::a4:
      case Field::a5:
      case Field::a6:
      case Field::a7:
      case Field::a8:
           return 'a';
      case Field::b1:
      case Field::b2:
      case Field::b3:
      case Field::b4:
      case Field::b5:
      case Field::b6:
      case Field::b7:
      case Field::b8:
           return 'b';
      case Field::c1:
      case Field::c2:
      case Field::c3:
      case Field::c4:
      case Field::c5:
      case Field::c6:
      case Field::c7:
      case Field::c8:
           return 'c';
      case Field::d1:
      case Field::d2:
      case Field::d3:
      case Field::d4:
      case Field::d5:
      case Field::d6:
      case Field::d7:
      case Field::d8:
           return 'd';
      case Field::e1:
      case Field::e2:
      case Field::e3:
      case Field::e4:
      case Field::e5:
      case Field::e6:
      case Field::e7:
      case Field::e8:
           return 'e';
      case Field::f1:
      case Field::f2:
      case Field::f3:
      case Field::f4:
      case Field::f5:
      case Field::f6:
      case Field::f7:
      case Field::f8:
           return 'f';
      case Field::g1:
      case Field::g2:
      case Field::g3:
      case Field::g4:
      case Field::g5:
      case Field::g6:
      case Field::g7:
      case Field::g8:
           return 'g';
      case Field::h1:
      case Field::h2:
      case Field::h3:
      case Field::h4:
      case Field::h5:
      case Field::h6:
      case Field::h7:
      case Field::h8:
           return 'h';
      case Field::none:
      default:
           throw std::invalid_argument("None is not allowed as argument of column()!");
    } // switch
  }


  /** \brief Gets the row/rank of a given field.
   *
   * \param  f a field, must not be none
   * \return Returns the row/rank of the given field.
   */
  constexpr int row(const Field f)
  {
    switch (f)
    {
      case Field::a1:
      case Field::b1:
      case Field::c1:
      case Field::d1:
      case Field::e1:
      case Field::f1:
      case Field::g1:
      case Field::h1:
           return 1;
      case Field::a2:
      case Field::b2:
      case Field::c2:
      case Field::d2:
      case Field::e2:
      case Field::f2:
      case Field::g2:
      case Field::h2:
           return 2;
      case Field::a3:
      case Field::b3:
      case Field::c3:
      case Field::d3:
      case Field::e3:
      case Field::f3:
      case Field::g3:
      case Field::h3:
           return 3;
      case Field::a4:
      case Field::b4:
      case Field::c4:
      case Field::d4:
      case Field::e4:
      case Field::f4:
      case Field::g4:
      case Field::h4:
           return 4;
      case Field::a5:
      case Field::b5:
      case Field::c5:
      case Field::d5:
      case Field::e5:
      case Field::f5:
      case Field::g5:
      case Field::h5:
           return 5;
      case Field::a6:
      case Field::b6:
      case Field::c6:
      case Field::d6:
      case Field::e6:
      case Field::f6:
      case Field::g6:
      case Field::h6:
           return 6;
      case Field::a7:
      case Field::b7:
      case Field::c7:
      case Field::d7:
      case Field::e7:
      case Field::f7:
      case Field::g7:
      case Field::h7:
           return 7;
      case Field::a8:
      case Field::b8:
      case Field::c8:
      case Field::d8:
      case Field::e8:
      case Field::f8:
      case Field::g8:
      case Field::h8:
           return 8;
      case Field::none:
      default:
           throw std::invalid_argument("None is not allowed as argument of row()!");
    } // switch
  }


  /** \brief Converts a (column;row) pair to Field.
   *
   * \param column column (file) of the field
   * \param row    row (rank) of the field
   * \return Returns the converted field.
   */
  constexpr Field toField(const char column, const int row)
  {
    if ((column < 'a') || (column > 'h') || (row < 1) || (row > 8))
      throw std::range_error("Column or row argument is out of range!");
    return static_cast<Field>((column - 'a') * 8 + (row - 1) + static_cast<int>(Field::a1));
  }


  /** \brief Determines whether both fields have the same file.
   *
   * \param f1  first field
   * \param f2  second field
   * \return Returns true, if both fields have the same file.
   *         Returns false otherwise, or if one of the fields is none.
   */
  constexpr bool sameFile(const Field f1, const Field f2)
  {
    return (f1 != Field::none) && (f2 != Field::none) && (column(f1) == column(f2));
  }


  /** \brief Determines whether both fields have the same rank.
   *
   * \param f1  first field
   * \param f2  second field
   * \return Returns true, if both fields have the same rank.
   *         Returns false otherwise, or if one of the fields is none.
   */
  constexpr bool sameRank(const Field f1, const Field f2)
  {
    return (f1 != Field::none) && (f2 != Field::none) && (row(f1) == row(f2));
  }

  /** \brief Gets the field left of the given field, as seen from the white player's perspective.
   *
   * \param f the field
   * \return Returns the field to the left of the given field, i.e. a1 for b1.
   * Returns Field::none, if there is no left field.
   */
  Field leftField(const Field f);

  /** \brief Gets the field right of the given field, as seen from the white player's perspective.
   *
   * \param f the field
   * \return Returns the field to the right of the given field, i.e. a1 for b1.
   * Returns Field::none, if there is no right field.
   */
  Field rightField(const Field f);
} // namespace

#endif // SIMPLE_CHESS_FIELD_HPP
