/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016  Dirk Stolle

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

#ifndef SIMPLE_CHESS_BOARD_HPP
#define SIMPLE_CHESS_BOARD_HPP

#include <map>
#include "colour.hpp"
#include "field.hpp"
#include "piece.hpp"

namespace simplechess
{

struct BoardElem
{
  Colour colour;
  Piece piece;

  BoardElem();
};

class Board
{
  std::map<Field, BoardElem> m_Fields;

  public:
    /* default constructor */
    Board();

    /* gets data for a given field on the board */
    const BoardElem& element(const Field f);
}; //class

} //namespace

#endif // SIMPLE_CHESS_BOARD_HPP
