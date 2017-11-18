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
#include "../../../evaluation/PromotionEvaluator.hpp"
#include "ConstantEvaluator.hpp"

TEST_CASE("CompoundEvaluator: empty compound evaluates to zero")
{
  using namespace simplechess;
  Board board;
  REQUIRE(board.fromFEN("4k3/8/Q7/8/8/8/8/4K3"));

  // Scores should be equal - both boards have the same number of moves.
  CompoundEvaluator evaluator;
  REQUIRE( evaluator.score(board) == 0 );
}

TEST_CASE("CompoundEvaluator: two evaluators")
{
  using namespace simplechess;
  Board board;
  REQUIRE(board.fromFEN("rn6/pK6/8/8/8/8/k7/8"));

  CompoundEvaluator evaluator;
  const int first = 300;
  const int second = 200;
  evaluator.add(std::unique_ptr<Evaluator>(new ConstantEvaluator(first)));
  evaluator.add(std::unique_ptr<Evaluator>(new ConstantEvaluator(second)));

  // Score should be sum of both evaluators.
  const int score = evaluator.score(board);
  REQUIRE( score == first + second );
}

TEST_CASE("CompoundEvaluator evaluates default start position")
{
  using namespace simplechess;
  Board board;
  REQUIRE(board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"));

  CompoundEvaluator evaluator;
  // Add the three evaluators we have so far.
  evaluator.add(std::unique_ptr<Evaluator>(new MaterialEvaluator()));
  evaluator.add(std::unique_ptr<Evaluator>(new MobilityEvaluator()));
  evaluator.add(std::unique_ptr<Evaluator>(new PromotionEvaluator()));

  // Evaluation should be zero - both sides have the same chances.
  REQUIRE( evaluator.score(board) == 0 );
}
