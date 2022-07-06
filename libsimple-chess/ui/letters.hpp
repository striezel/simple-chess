/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016, 2021, 2022  Dirk Stolle

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

#ifndef SIMPLE_CHESS_UI_LETTERS_HPP
#define SIMPLE_CHESS_UI_LETTERS_HPP

#include "../data/Piece.hpp"

namespace simplechess::ui
{

constexpr char letter_black(const PieceType t)
{
  switch(t)
  {
    case PieceType::pawn:
         return 'p';
    case PieceType::rook:
         return 'r';
    case PieceType::knight:
         return 'n';
    case PieceType::bishop:
         return 'b';
    case PieceType::queen:
         return 'q';
    case PieceType::king:
         return 'k';
    default:
         return ' ';
  }
}

constexpr char letter_white(const PieceType t)
{
  switch(t)
  {
    case PieceType::pawn:
         return 'P';
    case PieceType::rook:
         return 'R';
    case PieceType::knight:
         return 'N';
    case PieceType::bishop:
         return 'B';
    case PieceType::queen:
         return 'Q';
    case PieceType::king:
         return 'K';
    default:
         return ' ';
  }
}

/** \brief Gets the character representing the piece's symbol.
 *
 * \param p  the piece
 * \return Returns the character representing the piece's symbol.
 *         Returns space character for PieceType::none.
 */
constexpr char letter(const Piece& p)
{
  switch(p.colour())
  {
    case Colour::black:
         return letter_black(p.piece());
    default:
         return letter_white(p.piece());
  }
}

} // namespace

#endif // SIMPLE_CHESS_UI_LETTERS_HPP
