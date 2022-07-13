/*
 -------------------------------------------------------------------------------
    This file is part of the test suite for simple-chess.
    Copyright (C) 2017, 2018  Dirk Stolle

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


#include "../../locate_catch.hpp"
#include "../../../libsimple-chess/evaluation/CompoundEvaluator.hpp"
#include "../../../libsimple-chess/evaluation/MaterialEvaluator.hpp"
#include "../../../libsimple-chess/evaluation/LinearMobilityEvaluator.hpp"
#include "../../../libsimple-chess/rules/check.hpp"
#include "../../../libsimple-chess/search/Search.hpp"

TEST_CASE("Search: default start position with depth == 1")
{
  using namespace simplechess;
  Board board;
  REQUIRE(board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"));

  CompoundEvaluator evaluator;
  evaluator.add(std::unique_ptr<Evaluator>(new MaterialEvaluator()));
  evaluator.add(std::unique_ptr<Evaluator>(new LinearMobilityEvaluator()));
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
  evaluator.add(std::unique_ptr<Evaluator>(new LinearMobilityEvaluator()));
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

TEST_CASE("Search tree results must not put player in check")
{
  // This is a regression test for a scenario that occurred when the cli was
  // started with the position given below and black to move. Instead of moving
  // the black king out of check, the engine moved a pawn from c2 to c1. Of
  // course, this is against the rules, because black was still in check then.
  using namespace simplechess;
  Board board;

  // Position where black is in check, because white queen attacks black king.
  REQUIRE(board.fromFEN("rnb2bnN/ppp1k1pp/8/3BQ3/4P3/8/PPp2PPP/RN2K2R b"));
  // White player is not in check.
  REQUIRE_FALSE( isInCheck(board, Colour::white) );
  REQUIRE_FALSE( board.isInCheck(Colour::white) );
  // Black player is in check.
  REQUIRE( isInCheck(board, Colour::black) );
  REQUIRE( board.isInCheck(Colour::black) );

  CompoundEvaluator evaluator;
  evaluator.add(std::unique_ptr<Evaluator>(new MaterialEvaluator()));
  evaluator.add(std::unique_ptr<Evaluator>(new LinearMobilityEvaluator()));
  simplechess::Search s(board);
  REQUIRE( s.depth() == 0 );
  s.search(evaluator, 1);
  REQUIRE( s.depth() == 1 );
  const Node& searchNode = s.rootNode();
  bool found = false;
  // In each child position, black must not be in check anymore.
  for(const auto& child : searchNode.children)
  {
    // Must not be in check.
    REQUIRE_FALSE( child->board.isInCheck(Colour::black) );
    // Find move c2-c1 in list.
    if ((child->origin == Field::c2) && (child->destination == Field::c1))
      found = true;
  } // for

  // Move c2-c1 must not be in list.
  REQUIRE_FALSE( found );
}
