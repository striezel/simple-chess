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

#include "../locate_catch.hpp"
#include "../../../libsimple-chess/evaluation/CheckEvaluator.hpp"

TEST_CASE("CheckEvaluator evaluates default start position")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR") );

  CheckEvaluator evaluator;
  // Evaluation should be zero - nobody is in check.
  REQUIRE(
      evaluator.score(board) == 0
  );
}

TEST_CASE("CheckEvaluator: black is in check")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("4k3/8/8/8/8/8/4Q3/4K3") );

  // Evaluation should be greater than zero - white has an advantage.
  CheckEvaluator evaluator;
  const int score = evaluator.score(board);
  REQUIRE( score > 0 );
  REQUIRE( score == CheckEvaluator::defaultCheckValue );

  SECTION( "CheckEvaluator with custom check value" )
  {
    const int customValue = 123;
    const int customMateValue = 456;
    CheckEvaluator evaluator(customValue, customMateValue);
    const int score = evaluator.score(board);
    REQUIRE( score > 0 );
    REQUIRE( score == customValue );
  }
}

TEST_CASE("CheckEvaluator: black is not in check")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("4k3/pppppppp/8/8/8/8/4Q3/4K3") );

  // Evaluation should be zero - no player is in check.
  CheckEvaluator evaluator;
  const int score = evaluator.score(board);
  REQUIRE( score == 0 );

  SECTION( "CheckEvaluator with custom check value" )
  {
    const int customValue = 123;
    const int customMateValue = 456;
    CheckEvaluator evaluator(customValue, customMateValue);
    const int score = evaluator.score(board);
    REQUIRE( score == 0 );
  }
}

TEST_CASE("CheckEvaluator: white is in check")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("4k3/4q3/8/8/8/8/8/4K3") );

  // Evaluation should be less than zero - black has an advantage.
  CheckEvaluator evaluator;
  const int score = evaluator.score(board);
  REQUIRE( score < 0 );
  REQUIRE( score == -CheckEvaluator::defaultCheckValue );

  SECTION( "CheckEvaluator with custom check value" )
  {
    const int customValue = 123;
    const int customMateValue = 456;
    CheckEvaluator evaluator(customValue, customMateValue);
    const int score = evaluator.score(board);
    REQUIRE( score < 0 );
    REQUIRE( score == -customValue );
  }
}

TEST_CASE("CheckEvaluator: white is not in check")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("4k3/4q3/8/8/8/8/PPPPPPPP/4K3") );

  // Evaluation should be zero - no player is in check.
  CheckEvaluator evaluator;
  const int score = evaluator.score(board);
  REQUIRE( score == 0 );

  SECTION( "CheckEvaluator with custom check value" )
  {
    const int customValue = 123;
    const int customMateValue = 456;
    CheckEvaluator evaluator(customValue, customMateValue);
    const int score = evaluator.score(board);
    REQUIRE( score == 0 );
  }
}

TEST_CASE( "CheckEvaluator: white is checkmate" )
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("8/8/8/8/8/4r3/4q3/4K3") );

  // Evaluation should be less than zero - black has an advantage.
  CheckEvaluator evaluator;
  const int score = evaluator.score(board);
  REQUIRE( score < 0 );
  REQUIRE( score == -(CheckEvaluator::defaultCheckValue + CheckEvaluator::defaultCheckmateValue) );

  SECTION( "CheckEvaluator with custom check value" )
  {
    const int customValue = 123;
    const int customMateValue = 456;
    CheckEvaluator evaluator(customValue, customMateValue);
    const int score = evaluator.score(board);
    REQUIRE( score == -(customValue + customMateValue) );
  }
}

TEST_CASE( "CheckEvaluator: black is checkmate" )
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("8/8/8/8/8/4K3/4Q3/4k3 b") );

  // Evaluation should be greater than zero - white has an advantage.
  CheckEvaluator evaluator;
  const int score = evaluator.score(board);
  REQUIRE( score > 0 );
  REQUIRE( score == (CheckEvaluator::defaultCheckValue + CheckEvaluator::defaultCheckmateValue) );

  SECTION( "CheckEvaluator with custom check value" )
  {
    const int customValue = 123;
    const int customMateValue = 456;
    CheckEvaluator evaluator(customValue, customMateValue);
    const int score = evaluator.score(board);
    REQUIRE( score == (customValue + customMateValue) );
  }
}

TEST_CASE("CheckEvaluator: name")
{
  using namespace simplechess;

  SECTION( "CheckEvaluator with default values" )
  {
    CheckEvaluator evaluator;
    REQUIRE(
        evaluator.name() == "CheckEvaluator(50,2000000)"
    );
  }

  SECTION( "CheckEvaluator with custom values" )
  {
    CheckEvaluator evaluator(12, 3456);
    REQUIRE(
        evaluator.name() == "CheckEvaluator(12,3456)"
    );
  }
}
