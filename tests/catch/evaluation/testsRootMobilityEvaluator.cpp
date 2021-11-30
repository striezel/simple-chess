/*
 -------------------------------------------------------------------------------
    This file is part of the test suite for simple-chess.
    Copyright (C) 2018, 2020  Dirk Stolle

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
#include "../../../libsimple-chess/evaluation/RootMobilityEvaluator.hpp"
#include "../../../libsimple-chess/evaluation/LinearMobilityEvaluator.hpp"

TEST_CASE("RootMobilityEvaluator evaluates default start position")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR") );

  RootMobilityEvaluator evaluator;
  // Evaluation should be zero - both sides have the same move possibilities.
  REQUIRE( evaluator.score(board) == 0 );
}

TEST_CASE("RootMobilityEvaluator: kings only")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("4k3/8/8/8/8/8/8/4K3") );

  // Scores should be equal - both boards have the same number of moves.
  RootMobilityEvaluator evaluator;
  REQUIRE( evaluator.score(board) == 0 );
}

TEST_CASE("RootMobilityEvaluator: few black pieces only")
{
  using namespace simplechess;
  Board boardOne;
  REQUIRE( boardOne.fromFEN("rn6/pp6/8/8/8/8/8/8") );

  RootMobilityEvaluator evaluator;
  // Evaluation should be less than zero - black has more moves.
  const int scoreOne = evaluator.score(boardOne);
  REQUIRE( scoreOne < 0 );

  Board boardTwo;
  REQUIRE( boardTwo.fromFEN("rn6/1p6/8/8/8/8/8/8") );

  // Evaluation should be less than zero - black has more moves.
  const int scoreTwo = evaluator.score(boardTwo);
  REQUIRE( scoreTwo < 0 );

  // Second score should be even less, because black has now even more moves.
  REQUIRE( scoreTwo < scoreOne );
}

TEST_CASE("RootMobilityEvaluator: one king only, white edition")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("8/8/8/8/8/8/8/4K3") );

  RootMobilityEvaluator evaluator;
  // Evaluation should be greater than zero, because black has no moves.
  REQUIRE(
      evaluator.score(board) > 0
  );

  // Five moves in total, score should reflect that.
  //  Note: Square root of five is ca. 2.236.
  REQUIRE(
      evaluator.score(board) == static_cast<int>(2.236 * RootMobilityEvaluator::centipawnsPerMove)
  );
}

TEST_CASE("RootMobilityEvaluator: one king only, black edition")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("4k3/8/8/8/8/8/8/8") );

  RootMobilityEvaluator evaluator;
  // Evaluation should be less than zero, because white has no moves.
  REQUIRE(
      evaluator.score(board) < 0
  );

  // Five moves in total, score should reflect that.
  //  Note: Square root of five is ca. 2.236.
  REQUIRE(
      evaluator.score(board) == static_cast<int>(-2.236 * RootMobilityEvaluator::centipawnsPerMove)
  );
}

TEST_CASE("RootMobilityEvaluator vs. LinearMobilityEvaluator")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("8/8/8/8/8/8/RN6/1P6") );

  RootMobilityEvaluator rootEvaluator;
  LinearMobilityEvaluator linearEvaluator;
  // Evaluation should be greater than zero - white has more moves.
  const int scoreRoot = rootEvaluator.score(board);
  REQUIRE( scoreRoot > 0 );
  const int scoreLinear = linearEvaluator.score(board);
  REQUIRE( scoreLinear > 0 );

  // Score of root mobility evaluator should be less than the score of the
  // linear mobility evaluator, because root increases slower than identity.
  REQUIRE( scoreRoot < scoreLinear );
}

TEST_CASE("RootMobilityEvaluator: name")
{
  using namespace simplechess;

  RootMobilityEvaluator evaluator;
  REQUIRE(
      evaluator.name() == "RootMobilityEvaluator(10)"
  );
}
