/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2018, 2021, 2022, 2024  Dirk Stolle

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
#include <algorithm>
#include <map>
#include "../rules/Moves.hpp"

namespace simplechess
{

Search::Search(const Board& board)
: root(board, Field::none, Field::none, PieceType::none, 0),
  searchDepth(0)
{
}

void Search::search(const Evaluator& eval, const unsigned int depth)
{
  // Currently only up to one ply may be searched, because deeper levels of the
  // search tree will not be looked into when getting the best move. Yet.
  const unsigned int maximumSearchDepth = 2;

  // Clear children, if any.
  root.children.clear();
  // The real search depth must not be zero (std::max(1u, ...) takes care of that),
  // so that we get at least some moves. The search depth must also not be
  // greater than the maximum supported search depth (the std::min(...) part
  // takes care of that) to avoid exhaustive time and resource consumption.
  searchDepth = std::max(1u , std::min(depth, maximumSearchDepth));
  // Expand search node into tree.
  expandNode(root, eval, searchDepth);
}

std::tuple<Field, Field, PieceType> Search::bestMove() const
{
  // If there are no moves, then there's nothing we can do here.
  if (!hasMove())
  {
    return std::tuple<Field, Field, PieceType>(Field::none, Field::none, PieceType::none);
  }
  if (searchDepth >= 2)
    return bestMoveTwoPly();
  else
    return bestMoveOnePly();
}

std::tuple<Field, Field, PieceType> Search::bestMoveOnePly() const
{
  // Simple strategy: Get the move with the minimum or maximum score, depending
  // on the side who is to move in the original position. Since the child nodes
  // of an expanded search node are sorted by score in ascending order, the 1st
  // (or front) node has the lowest score, and the last (or back) node has the
  // highest score.
  Field from = Field::none;
  Field to = Field::none;
  PieceType promo = PieceType::queen;
  if (root.board.toMove() == Colour::black)
  {
    from = root.children.front()->origin;
    to = root.children.front()->destination;
    promo = root.children.front()->promoteTo;
  }
  else
  {
    from = root.children.back()->origin;
    to = root.children.back()->destination;
    promo = root.children.back()->promoteTo;
  }
  return std::tuple<Field, Field, PieceType>(from, to, promo);
}

std::tuple<Field, Field, PieceType> Search::bestMoveTwoPly() const
{
  // Basic idea: The best move is the one where the best possible reply of the
  // opponent has the worst score for the opponent. Even better are the moves
  // where the opponent has no reply at all, because that usually means
  // checkmate.

  // First: Search for checkmate moves.
  for (const auto& node : root.children)
  {
    if (node->children.empty())
    {
      return std::tuple<Field, Field, PieceType>(
          node->origin, node->destination, node->promoteTo);
    }
  } // for

  // Search for move with worst possible best reply of opponent.
  std::map<std::size_t, int> idxWithScore;
  for (std::size_t i = 0; i < root.children.size(); ++i)
  {
    // Use first possible reply as initial value. (At least one reply must
    // exist, because otherwise it would have been handled by the first search
    // for checkmate.)
    idxWithScore[i] = root.children[i]->children[0]->score;
    // Loop through remaining replies. First reply (index 0) can be omitted.
    for (std::size_t j = 1; j < root.children[i]->children.size(); ++j)
    {
      if (root.board.toMove() == Colour::black)
      {
        // Engine plays black. That means best score for white is max. score.
        if (root.children[i]->children[j]->score > idxWithScore[i])
        {
          idxWithScore[i] = root.children[i]->children[j]->score;
        }
      } // if
      else
      {
        // Engine plays white. That means best score for black is min. score.
        if (root.children[i]->children[j]->score < idxWithScore[i])
        {
          idxWithScore[i] = root.children[i]->children[j]->score;
        }
      } // else
    } // for
  } // for

  // Find best (for current player).
  std::size_t bestIdx = 0;
  if (root.board.toMove() == Colour::black)
  {
    for (std::size_t i = 1; i < root.children.size(); ++i)
    {
      if (idxWithScore[i] < idxWithScore[bestIdx])
      {
        bestIdx = i;
      }
    }
  } // if
  else // player == white
  {
    for (std::size_t i = 1; i < root.children.size(); ++i)
    {
      if (idxWithScore[i] > idxWithScore[bestIdx])
      {
        bestIdx = i;
      }
    }
  } // else
  return std::tuple<Field, Field, PieceType>(
          root.children[bestIdx]->origin, root.children[bestIdx]->destination,
          root.children[bestIdx]->promoteTo);
}

const Node& Search::rootNode() const
{
  return root;
}

unsigned int Search::depth() const
{
  return searchDepth;
}

bool Search::hasMove() const
{
  return !root.children.empty();
}

std::tuple<Field, Field, PieceType> Search::search(const Board& board, const Evaluator& eval, const unsigned int depth)
{
  Search s(board);
  s.search(eval, depth);
  return s.bestMove();
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
    if ((elem.colour() != node.board.toMove()) || (elem.piece() == PieceType::none))
      continue;
    // check possible moves
    for (int j = static_cast<int>(Field::a1); j <= static_cast<int>(Field::h8); ++j)
    {
      const Field from = static_cast<Field>(i);
      const Field to = static_cast<Field>(j);
      if (Moves::isAllowed(node.board, from, to))
      {
        // Default: Not a pawn promotion.
        if (!Moves::isPromotion(node.board, from, to))
        {
          Board movedBoard(node.board);
          movedBoard.move(from, to, PieceType::queen);
          node.children.push_back(
              std::unique_ptr<Node>(
              new Node(movedBoard, from, to, PieceType::queen,
              eval.score(movedBoard))));
        } // if not pawn promotion
        else
        {
          // Same move but with different promotions.
          const auto types = { PieceType::queen, PieceType::knight, PieceType::bishop, PieceType::rook };
          for ( const auto promo : types )
          {
            Board movedBoard(node.board);
            movedBoard.move(from, to, promo);
            node.children.push_back(
                std::unique_ptr<Node>(
                new Node(movedBoard, from, to, promo,
                eval.score(movedBoard))));
          } // for
        } // else (It's a pawn promotion.)
      } // if move is allowed
    } // for j
  } // for i
  // sort children
  node.sortChildren();
  // expand child nodes
  for(auto& child : node.children)
  {
    expandNode(*child, eval, depth - 1);
  } // for
}

} // namespace
