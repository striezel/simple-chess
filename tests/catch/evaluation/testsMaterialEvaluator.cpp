/*
 -------------------------------------------------------------------------------
    This file is part of the test suite for simple-chess.
    Copyright (C) 2017, 2020  Dirk Stolle

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
#include "../../../evaluation/MaterialEvaluator.hpp"

TEST_CASE("MaterialEvaluator evaluates default start position")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR") );

  MaterialEvaluator evaluator;
  // Evaluation should be zero - both sides have the same material.
  REQUIRE(
      evaluator.score(board) == 0
  );
}

TEST_CASE("MaterialEvaluator: different position with same material should not change score")
{
  using namespace simplechess;
  Board boardOne;
  REQUIRE( boardOne.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR") );

  Board boardTwo;
  REQUIRE( boardTwo.fromFEN("rnbqkbnr/pppp1ppp/4p3/8/8/4P3/PPPP1PPP/RNBQKBNR") );

  // Scores should be equal - both boards have the same amount of material.
  MaterialEvaluator evaluator;
  REQUIRE(
      evaluator.score(boardOne) == evaluator.score(boardTwo)
  );
}

TEST_CASE("MaterialEvaluator: one missing rook for white")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/1NBQKBNR") );

  MaterialEvaluator evaluator;
  // Evaluation should be less than zero - black has more.
  REQUIRE(
      evaluator.score(board) < 0
  );
  // Rook is five pawns, so value should be -500 centipawns.
  REQUIRE(
      evaluator.score(board) == -500
  );
}

TEST_CASE("MaterialEvaluator: one missing rook for black")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("1nbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR") );

  MaterialEvaluator evaluator;
  // Evaluation should be greater than zero - white has more material.
  REQUIRE(
      evaluator.score(board) > 0
  );
  // Rook is five pawns, so value should be 500 centipawns.
  REQUIRE(
      evaluator.score(board) == 500
  );
}

TEST_CASE("MaterialEvaluator: one king to rule them all, white edition")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("rnbqqbnr/pppppppp/qqqqqqqq/qqqqqqqq/qqqqqqqq/qqqqqqqq/qqqqqqqq/4K3") );

  MaterialEvaluator evaluator;
  // Evaluation should be greater than zero, because black has no king and thus
  // has lost.
  REQUIRE(
      evaluator.score(board) > 0
  );
}

TEST_CASE("MaterialEvaluator: one king to rule them all, black edition")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("4k3/QQQQQQQQ/QQQQQQQQ/QQQQQQQQ/QQQQQQQQ/QQQQQQQQ/PPPPPPPP/RNBQQBNR") );

  MaterialEvaluator evaluator;
  // Evaluation should be less than zero, because white has no king and thus
  // has lost.
  REQUIRE(
      evaluator.score(board) < 0
  );
}

TEST_CASE("MaterialEvaluator: name")
{
  using namespace simplechess;

  MaterialEvaluator evaluator;
  REQUIRE(
      evaluator.name() == "MaterialEvaluator"
  );
}
