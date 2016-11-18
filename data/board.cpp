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

#include "board.hpp"

namespace simplechess
{

BoardElem::BoardElem()
: colour(Colour::none),
  piece(Piece::none)
{
}

Board::Board()
{
  for(int i = static_cast<int>(Field::a1); i <= static_cast<int>(Field::h8); ++i)
  {
    m_Fields[static_cast<Field>(i)] = BoardElem();
  }
}

const BoardElem& Board::element(const Field f)
{
  const std::map<Field, BoardElem>::const_iterator cIter = m_Fields.find(f);
  if (cIter != m_Fields.end())
    return cIter->second;
  throw std::runtime_error("Field does not exist on board!");
}

} //namespace
