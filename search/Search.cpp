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

#include "Search.hpp"
#include "../rules/Moves.hpp"

namespace simplechess
{

Node Search::search(const Board& board, const Evaluator& eval, const unsigned int depth)
{
  Node current(board, Field::none, Field::none, PieceType::none, 0);
  expandNode(current, eval, depth);
  return std::move(current);
}

void Search::expandNode(Node& node, const Evaluator& eval, const unsigned int depth)
{
  if (depth <= 0)
  {
    return;
  }
  for (int i = static_cast<int>(Field::a1); i <= static_cast<int>(Field::h8); ++i)
  {
    const Piece elem = node.board.element(static_cast<Field>(i));
    if ((elem.colour != node.board.toMove()) || (elem.piece == PieceType::none))
      continue;
    // check possible moves
    for (int j = static_cast<int>(Field::a1); j <= static_cast<int>(Field::h8); ++j)
    {
      const Field from = static_cast<Field>(i);
      const Field to = static_cast<Field>(j);
      if (Moves::allowed(node.board, from, to))
      {
        Board movedBoard(node.board);
        // TODO: Check other promotions, too.
        movedBoard.move(from, to, PieceType::queen);
        node.children.push_back(
            std::unique_ptr<Node>(
            new Node(movedBoard, from, to, PieceType::queen,
            eval.score(movedBoard))));
      } //if move is allowed
    } //for j
  } //for i
  // sort children
  node.sortChildren();
  // expand child nodes
  for(auto& child : node.children)
  {
    expandNode(*child, eval, depth - 1);
  } //for
}

} //namespace
