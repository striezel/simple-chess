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

#include "Node.hpp"
#include <algorithm>

namespace simplechess
{

Node::Node()
: board(Board()),
  origin(Field::none),
  destination(Field::none),
  promoteTo(PieceType::none),
  score(0),
  children(std::vector<std::unique_ptr<Node>>())
{
}

Node::Node(const Board& b, const Field& orig, const Field& dest, const PieceType& promo, const int _score)
: board(b),
  origin(orig),
  destination(dest),
  promoteTo(promo),
  score(_score),
  children(std::vector<std::unique_ptr<Node>>())
{
}

bool lessNode(const std::unique_ptr<Node>& a, const std::unique_ptr<Node>& b)
{
  return a->score < b->score;
}

void Node::sortChildren()
{
  std::sort(children.begin(), children.end(), lessNode);
}

} //namespace
