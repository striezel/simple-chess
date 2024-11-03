/*
 -------------------------------------------------------------------------------
    This file is part of the test suite for simple-chess.
    Copyright (C) 2017, 2020, 2024  Dirk Stolle

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
#include "../../../libsimple-chess/evaluation/MaterialEvaluator.hpp"

TEST_CASE("MaterialEvaluator")
{
  using namespace simplechess;

  SECTION("score()")
  {
    MaterialEvaluator evaluator;

    SECTION("evaluate default start position")
    {
      Board board;
      REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR") );

      // Evaluation should be zero - both sides have the same material.
      REQUIRE(
          evaluator.score(board) == 0
      );
    }

    SECTION("different position with same material should not change score")
    {
      Board boardOne;
      REQUIRE( boardOne.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR") );

      Board boardTwo;
      REQUIRE( boardTwo.fromFEN("rnbqkbnr/pppp1ppp/4p3/8/8/4P3/PPPP1PPP/RNBQKBNR") );

      // Scores should be equal - both boards have the same amount of material.
      REQUIRE(
          evaluator.score(boardOne) == evaluator.score(boardTwo)
      );
    }

    SECTION("one missing rook for white")
    {
      Board board;
      REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/1NBQKBNR") );

      // Evaluation should be less than zero - black has more.
      REQUIRE(
          evaluator.score(board) < 0
      );
      // Rook is five pawns, so value should be -500 centipawns.
      REQUIRE(
          evaluator.score(board) == -500
      );
    }

    SECTION("one missing rook for black")
    {
      Board board;
      REQUIRE( board.fromFEN("1nbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR") );

      // Evaluation should be greater than zero - white has more material.
      REQUIRE(
          evaluator.score(board) > 0
      );
      // Rook is five pawns, so value should be 500 centipawns.
      REQUIRE(
          evaluator.score(board) == 500
      );
    }

    SECTION("one king to rule them all, white edition")
    {
      Board board;
      REQUIRE( board.fromFEN("rnbqqbnr/pppppppp/qqqqqqqq/qqqqqqqq/qqqqqqqq/qqqqqqqq/qqqqqqqq/4K3") );

      // Evaluation should be greater than zero, because black has no king and
      // thus has lost.
      REQUIRE(
          evaluator.score(board) > 0
      );
    }

    SECTION("one king to rule them all, black edition")
    {
      Board board;
      REQUIRE( board.fromFEN("4k3/QQQQQQQQ/QQQQQQQQ/QQQQQQQQ/QQQQQQQQ/QQQQQQQQ/PPPPPPPP/RNBQQBNR") );

      // Evaluation should be less than zero, because white has no king and
      // thus has lost.
      REQUIRE(
          evaluator.score(board) < 0
      );
    }
  }

  SECTION("name")
  {
    MaterialEvaluator evaluator;
    REQUIRE(
        evaluator.name() == "MaterialEvaluator"
    );
  }

  SECTION("pieceValue")
  {
    REQUIRE( MaterialEvaluator::pieceValue(PieceType::none) == 0 );
    REQUIRE( MaterialEvaluator::pieceValue(PieceType::pawn) == 100 );
    REQUIRE( MaterialEvaluator::pieceValue(PieceType::bishop) == 325 );
    REQUIRE( MaterialEvaluator::pieceValue(PieceType::knight) == 300 );
    REQUIRE( MaterialEvaluator::pieceValue(PieceType::rook) == 500 );
    REQUIRE( MaterialEvaluator::pieceValue(PieceType::queen) == 900 );
    REQUIRE( MaterialEvaluator::pieceValue(PieceType::king) > 900 );
  }
}
