/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2022  Dirk Stolle

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

#ifndef SIMPLE_CHESS_UI_SYMBOLS_HPP
#define SIMPLE_CHESS_UI_SYMBOLS_HPP

#include <string_view>

namespace simplechess::ui
{

constexpr std::string_view symbol_black(const PieceType t)
{
  using namespace std::string_view_literals;

  switch(t)
  {
    case PieceType::king:
         return "\xE2\x99\x9A"sv;
    case PieceType::queen:
         return "\xE2\x99\x9B"sv;
    case PieceType::rook:
         return "\xE2\x99\x9C"sv;
    case PieceType::bishop:
         return "\xE2\x99\x9D"sv;
    case PieceType::knight:
         return "\xE2\x99\x9E"sv;
    case PieceType::pawn:
         return "\xE2\x99\x9F"sv;
    default:
         return " "sv;
  }
}

constexpr std::string_view symbol_white(const PieceType t)
{
  using namespace std::string_view_literals;

  switch(t)
  {
    case PieceType::king:
         return "\xE2\x99\x94"sv;
    case PieceType::queen:
         return "\xE2\x99\x95"sv;
    case PieceType::rook:
         return "\xE2\x99\x96"sv;
    case PieceType::bishop:
         return "\xE2\x99\x97"sv;
    case PieceType::knight:
         return "\xE2\x99\x98"sv;
    case PieceType::pawn:
         return "\xE2\x99\x99"sv;
    default:
         return " "sv;
  }
}

/** \brief Gets the UTF-8 sequence containing the piece's symbol.
 *
 * \param p  the piece
 * \return Returns the UTF-8 sequence containing the piece's symbol.
 *         Returns space character for PieceType::none.
 */
std::string_view symbol(const Piece& p)
{
  switch(p.colour())
  {
    case Colour::black:
         return symbol_black(p.piece());
    default:
         return symbol_white(p.piece());
  }
}

} // namespace

#endif
