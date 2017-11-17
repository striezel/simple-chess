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
#include "../../../evaluation/MobilityEvaluator.hpp"

TEST_CASE("MobilityEvaluator evaluates default start position")
{
  using namespace simplechess;
  Board board;
  REQUIRE(board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"));

  MobilityEvaluator evaluator;
  // Evaluation should be zero - both sides have the same material.
  REQUIRE( evaluator.score(board) == 0 );
}

TEST_CASE("MobilityEvaluator: kings only")
{
  using namespace simplechess;
  Board board;
  REQUIRE(board.fromFEN("4k3/8/8/8/8/8/8/4K3"));

  // Scores should be equal - both boards have the same number of moves.
  MobilityEvaluator evaluator;
  REQUIRE( evaluator.score(board) == 0 );
}

TEST_CASE("MobilityEvaluator: one missing rook for white")
{
  using namespace simplechess;
  Board boardOne;
  REQUIRE(boardOne.fromFEN("rn6/pp6/8/8/8/8/8/8"));

  MobilityEvaluator evaluator;
  // Evaluation should be less than zero - black has more moves.
  const int scoreOne = evaluator.score(boardOne);
  REQUIRE( scoreOne < 0 );

  Board boardTwo;
  REQUIRE(boardTwo.fromFEN("rn6/1p6/8/8/8/8/8/8"));

  // Evaluation should be less than zero - black has more moves.
  const int scoreTwo = evaluator.score(boardTwo);
  REQUIRE( scoreTwo < 0 );

  // Second score should be even less, because black has now even more moves.
  REQUIRE( scoreTwo < scoreOne );

  REQUIRE( (scoreTwo + 5 * MobilityEvaluator::centipawnsPerMove) == scoreOne );
}

TEST_CASE("MobilityEvaluator: one king only, white edition")
{
  using namespace simplechess;
  Board board;
  REQUIRE(board.fromFEN("8/8/8/8/8/8/8/4K3"));

  MobilityEvaluator evaluator;
  // Evaluation should be greater than zero, because black has no moves.
  REQUIRE(
      evaluator.score(board) > 0
  );

  // Five moves in total, score should reflect that.
  REQUIRE(
      evaluator.score(board) == 5 * MobilityEvaluator::centipawnsPerMove
  );
}

TEST_CASE("MaterialEvaluator: one king only, black edition")
{
  using namespace simplechess;
  Board board;
  REQUIRE(board.fromFEN("4k3/8/8/8/8/8/8/8"));

  MobilityEvaluator evaluator;
  // Evaluation should be less than zero, because white has no moves.
  REQUIRE(
      evaluator.score(board) < 0
  );

  // Five moves in total, score should reflect that.
  REQUIRE(
      evaluator.score(board) == -5 * MobilityEvaluator::centipawnsPerMove
  );
}
