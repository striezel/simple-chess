/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016, 2021  Dirk Stolle

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

#include "Console.hpp"
#include <iostream>

namespace simplechess::ui
{

void Console::showBoard(const Board & board)
{
  const std::string rowSeparator = "+---+---+---+---+---+---+---+---+";
  std::cout << rowSeparator << "\n";
  for (int r = 8; r >= 1; r--)
  {
    std::cout << "| ";
    for (char c = 'a'; c <= 'h'; ++c)
    {
      const Piece & piece = board.element(toField(c, r));
      char output = '?';
      switch (piece.colour())
      {
        case Colour::none:
             output = ' ';
             break;
        case Colour::white:
             switch(piece.piece())
             {
               case PieceType::pawn:
                    output = 'P';
                    break;
               case PieceType::rook:
                    output = 'R';
                    break;
               case PieceType::knight:
                    output = 'N';
                    break;
               case PieceType::bishop:
                    output = 'B';
                    break;
               case PieceType::queen:
                    output = 'Q';
                    break;
               case PieceType::king:
                    output = 'K';
                    break;
               default:
                    output = 'X';
                    break;
             } //inner switch
             break;
        case Colour::black:
             switch(piece.piece())
             {
               case PieceType::pawn:
                    output = 'p';
                    break;
               case PieceType::rook:
                    output = 'r';
                    break;
               case PieceType::knight:
                    output = 'n';
                    break;
               case PieceType::bishop:
                    output = 'b';
                    break;
               case PieceType::queen:
                    output = 'q';
                    break;
               case PieceType::king:
                    output = 'k';
                    break;
               default:
                    output = 'X';
                    break;
             } //inner switch
             break;
      } // colour
      std::cout << output << " | ";
    } // for c
    std::cout << "\n" << rowSeparator << "\n";
  } // for r
}

} // namespace
