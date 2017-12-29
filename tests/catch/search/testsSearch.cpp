/*
 -------------------------------------------------------------------------------
    This file is part of the test suite for simple-chess.
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


#include <catch.hpp>
#include "../../../evaluation/CompoundEvaluator.hpp"
#include "../../../evaluation/MaterialEvaluator.hpp"
#include "../../../evaluation/MobilityEvaluator.hpp"
#include "../../../rules/check.hpp"
#include "../../../search/Search.hpp"

TEST_CASE("Search: default start position with depth == 1")
{
  using namespace simplechess;
  Board board;
  REQUIRE(board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"));

  CompoundEvaluator evaluator;
  evaluator.add(std::unique_ptr<Evaluator>(new MaterialEvaluator()));
  evaluator.add(std::unique_ptr<Evaluator>(new MobilityEvaluator()));
  simplechess::Search s(board);
  REQUIRE( s.depth() == 0 );
  s.search(evaluator, 1);
  REQUIRE( s.depth() == 1 );
  const Node& searchNode = s.rootNode();

  // There should be some child nodes.
  REQUIRE_FALSE( searchNode.children.empty() );
  // ... and that means the search has some moves.
  REQUIRE( s.hasMove() );
  // Number of child nodes should be 20, because there are 20 possible moves.
  REQUIRE( searchNode.children.size() == 20 );
  // Child nodes should be ordered by score.
  for (std::size_t i = 0; i < searchNode.children.size() - 1; ++i)
  {
    for (std::size_t j = i + 1; j < searchNode.children.size(); ++j)
    {
      REQUIRE( searchNode.children[i]->score <= searchNode.children[j]->score );
    } // for j
  } // for i

  // Score of first node should be less than that of the last node.
  REQUIRE( searchNode.children.front()->score < searchNode.children.back()->score );

  // Child nodes of child nodes should be empty, because depth is only one.
  for(const auto& child : searchNode.children)
  {
    REQUIRE( child->children.empty() );
  }

  // There must be a best move, i.e. its members must not equal none.
  const auto bestMove = s.bestMove();
  REQUIRE( std::get<0>(bestMove) != Field::none );
  REQUIRE( std::get<1>(bestMove) != Field::none );
  REQUIRE( std::get<2>(bestMove) != PieceType::none );
}

TEST_CASE("Search: default start position with depth == 2")
{
  using namespace simplechess;
  Board board;
  REQUIRE(board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"));

  CompoundEvaluator evaluator;
  evaluator.add(std::unique_ptr<Evaluator>(new MaterialEvaluator()));
  evaluator.add(std::unique_ptr<Evaluator>(new MobilityEvaluator()));
  simplechess::Search s(board);
  REQUIRE( s.depth() == 0 );
  s.search(evaluator, 2);
  REQUIRE( s.depth() == 2 );
  const Node& searchNode = s.rootNode();

  // There should be some child nodes.
  REQUIRE_FALSE( searchNode.children.empty() );
  // ... and that means the search has some moves.
  REQUIRE( s.hasMove() );
  // Number of child nodes should be 20, because there are 20 possible moves.
  REQUIRE( searchNode.children.size() == 20 );
  // Child nodes should be ordered by score.
  for (std::size_t i = 0; i < searchNode.children.size() - 1; ++i)
  {
    for (std::size_t j = i + 1; j < searchNode.children.size(); ++j)
    {
      REQUIRE( searchNode.children[i]->score <= searchNode.children[j]->score );
    } // for j
  } // for i

  // Child nodes of child nodes should not be empty, because depth is two.
  for(const auto& child : searchNode.children)
  {
    REQUIRE_FALSE( child->children.empty() );

    // Child nodes of child should be ordered by score, too.
    for (std::size_t i = 0; i < child->children.size() - 1; ++i)
    {
      for (std::size_t j = i + 1; j < child->children.size(); ++j)
      {
        REQUIRE( child->children[i]->score <= child->children[j]->score );
      } // for j
    } // for i
  } // outer for

  // There must be a best move, i.e. its members must not equal none.
  const auto bestMove = s.bestMove();
  REQUIRE( std::get<0>(bestMove) != Field::none );
  REQUIRE( std::get<1>(bestMove) != Field::none );
  REQUIRE( std::get<2>(bestMove) != PieceType::none );
}
