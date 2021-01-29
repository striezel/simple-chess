/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016, 2017, 2018, 2021  Dirk Stolle

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

#include "ForsythEdwardsNotation.hpp"
#include "../util/strings.hpp"

namespace simplechess
{

const std::string ForsythEdwardsNotation::defaultInitialPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0";

std::string ForsythEdwardsNotation::fromBoard(const Board & board)
{
  int emptyCount = 0;
  std::string fenString = "";
  for (int r = 8; r >= 1; --r)
  {
    for (char c = 'a'; c <= 'h'; ++c)
    {
      const Piece & piece = board.element(toField(c, r));
      if (piece.piece() == PieceType::none)
        ++emptyCount;
      else
      {
        // First, add empty count, if any.
        if (emptyCount > 0)
        {
          fenString = fenString + util::intToString(emptyCount);
          emptyCount = 0;
        }
        // now add the real thing
        switch(piece.colour())
        {
          case Colour::white:
               switch(piece.piece())
               {
                 case PieceType::rook:
                      fenString = fenString + 'R';
                      break;
                 case PieceType::knight:
                      fenString = fenString + 'N';
                      break;
                 case PieceType::bishop:
                      fenString = fenString + 'B';
                      break;
                 case PieceType::queen:
                      fenString = fenString + 'Q';
                      break;
                 case PieceType::king:
                      fenString = fenString + 'K';
                      break;
                 case PieceType::pawn:
                      fenString = fenString + 'P';
                      break;
                 default:
                      // invalid piece
                      return std::string();
               } // switch piece
               break;
          case Colour::black:
               switch(piece.piece())
               {
                 case PieceType::rook:
                      fenString = fenString + 'r';
                      break;
                 case PieceType::knight:
                      fenString = fenString + 'n';
                      break;
                 case PieceType::bishop:
                      fenString = fenString + 'b';
                      break;
                 case PieceType::queen:
                      fenString = fenString + 'q';
                      break;
                 case PieceType::king:
                      fenString = fenString + 'k';
                      break;
                 case PieceType::pawn:
                      fenString = fenString + 'p';
                      break;
                 default:
                      // invalid piece
                      return std::string();
               } // switch piece
               break;
          case Colour::none:
               // should never happen, invalid colour
               return std::string();
        } // switch colour
      } // else
    } // for columns
    // First, add empty count, if any.
    if (emptyCount > 0)
    {
      fenString = fenString + util::intToString(emptyCount);
      emptyCount = 0;
    }
    // add slash - except after last row
    if (r > 1)
      fenString = fenString + "/";
  } // for rows
  // Who is to move?
  switch(board.toMove())
  {
    case Colour::white:
         fenString = fenString + " w";
         break;
    case Colour::black:
         fenString = fenString + " b";
         break;
    default:
         // Something is wrong here, return without extra data.
         return fenString;
  } // switch
  // castling information
  fenString += " " + board.castling().toFEN();
  // en passant
  const Field & ep = board.enPassant();
  if (ep == Field::none)
    fenString = fenString + " -";
  else
    fenString = fenString + " " + column(ep) + util::intToString(row(ep));
  // number of half moves under 50 move rule
  fenString += (" " + util::intToString(board.halfmovesFifty()));
  // Return here, because other data is not implemented yet.
  return fenString;
}

} //namespace
