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
#include "../../../libsimple-chess/evaluation/PromotionEvaluator.hpp"

TEST_CASE("PromotionEvaluator evaluates default start position")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR") );

  PromotionEvaluator evaluator;
  // Evaluation should be zero - both sides have no pawns that can be promoted.
  REQUIRE(
      evaluator.score(board) == 0
  );
}

TEST_CASE("PromotionEvaluator: one promotable white pawn")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("8/pPpppppp/8/8/8/8/8/8") );

  // Evaluation should be greater than zero - white has more pawn promotions.
  PromotionEvaluator evaluator;
  const int score = evaluator.score(board);
  REQUIRE( score > 0 );
  REQUIRE( score == 900 );
}

TEST_CASE("PromotionEvaluator: one promotable black pawn")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("8/8/8/8/8/8/PpPPPPPP/8") );

  // Evaluation should be less than zero - black has more pawn promotions.
  PromotionEvaluator evaluator;
  const int score = evaluator.score(board);
  REQUIRE( score < 0 );
  REQUIRE( score == -900 );
}

TEST_CASE("PromotionEvaluator: blocked white pawn")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("1K6/pPpppppp/8/8/8/8/8/8") );

  // Evaluation should be zero - white pawn cannot be promoted.
  PromotionEvaluator evaluator;
  const int score = evaluator.score(board);
  REQUIRE( score == 0 );
}

TEST_CASE("PromotionEvaluator: blocked black pawn")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("8/8/8/8/8/8/PpPPPPPP/1k6") );

  // Evaluation should be zero - black pawn cannot be promoted.
  PromotionEvaluator evaluator;
  const int score = evaluator.score(board);
  REQUIRE( score == 0 );
}

TEST_CASE("PromotionEvaluator: blocked white pawn with alternative")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("Qb6/P7/8/8/8/8/8/8") );

  // Evaluation should be greater than zero - white pawn can be promoted by
  // capturing the black bishop.
  PromotionEvaluator evaluator;
  const int score = evaluator.score(board);
  REQUIRE( score > 0 );
  REQUIRE( score == 900 );
}

TEST_CASE("PromotionEvaluator: blocked black pawn with alternative")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("8/8/8/8/8/8/p7/qB6") );

  // Evaluation should be less than zero - black pawn can be promoted by
  // capturing the white bishop.
  PromotionEvaluator evaluator;
  const int score = evaluator.score(board);
  REQUIRE( score < 0 );
  REQUIRE( score == -900 );
}

TEST_CASE("PromotionEvaluator: multiple promotion possibilities for white")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("rnbqkbnr/PPPP4/8/8/8/8/4PPPP/1NBQKBNR") );

  PromotionEvaluator evaluator;
  // Evaluation should be more than zero - white has four possibilities.
  REQUIRE(
      evaluator.score(board) > 0
  );
  // Four possibilities equals four queens.
  REQUIRE(
      evaluator.score(board) == 4 * 900
  );
}

TEST_CASE("PromotionEvaluator: multiple promotion possibilities for black")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("rnbqkbnr/pppp4/8/8/8/8/4pppp/1NBQKBNR") );

  PromotionEvaluator evaluator;
  // Evaluation should be less than zero - black has four possibilities.
  REQUIRE(
      evaluator.score(board) < 0
  );
  // Four possibilities equals four queens.
  REQUIRE(
      evaluator.score(board) == -4 * 900
  );
}

TEST_CASE("PromotionEvaluator: three for white and two for black")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("rnbqkbnr/PPP5/8/8/8/8/6pp/1NBQKBNR") );

  PromotionEvaluator evaluator;
  // Evaluation should be greater than zero - white has more possibilities.
  REQUIRE(
      evaluator.score(board) > 0
  );
  // One more possibility equals one queen.
  REQUIRE(
      evaluator.score(board) == 900
  );
}

TEST_CASE("PromotionEvaluator: name")
{
  using namespace simplechess;

  PromotionEvaluator evaluator;
  REQUIRE(
      evaluator.name() == "PromotionEvaluator"
  );
}
