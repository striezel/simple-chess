/*
 -------------------------------------------------------------------------------
    This file is part of the test suite for simple-chess.
    Copyright (C) 2018  Dirk Stolle

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
#include "../../../evaluation/CastlingEvaluator.hpp"

TEST_CASE("CastlingEvaluator evaluates default start position")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR") );

  CastlingEvaluator evaluator;
  // Evaluation should be zero - nobody has forfeited castling yet.
  REQUIRE(
      evaluator.score(board) == 0
  );
}

TEST_CASE("CastlingEvaluator: white forfeits castling privileges")
{
  using namespace simplechess;
  Board board;
  CastlingEvaluator evaluator;

  SECTION( "move king to forfeit" )
  {
    REQUIRE( board.fromFEN("rnbqkbnr/1ppp1pp1/8/8/8/8/1PPP1PP1/RNBQKBNR") );
    // Score should be zero.
    const int score = evaluator.score(board);
    REQUIRE( score == 0 );
    REQUIRE( board.move(Field::e1, Field::e2, PieceType::queen) );
    REQUIRE_FALSE( board.castling().white_kingside );
    REQUIRE_FALSE( board.castling().white_queenside );
    REQUIRE( board.castling().white_castled == Ternary::false_value );
    // Score should be below zero, because black has advantage.
    const int newScore = evaluator.score(board);
    REQUIRE( newScore < 0 );
    REQUIRE( newScore == -CastlingEvaluator::defaultCastlingValue );
  }

  SECTION( "move rook on a to forfeit" )
  {
    REQUIRE( board.fromFEN("rnbqkbnr/1ppp1pp1/8/8/8/8/1PPP1PP1/RNBQKBN1") );
    // Score should be zero.
    const int score = evaluator.score(board);
    REQUIRE( score == 0 );
    REQUIRE( board.move(Field::a1, Field::a4, PieceType::queen) );
    REQUIRE_FALSE( board.castling().white_kingside );
    REQUIRE_FALSE( board.castling().white_queenside );
    REQUIRE( board.castling().white_castled == Ternary::false_value );
    // Score should be below zero, because black has advantage.
    const int newScore = evaluator.score(board);
    REQUIRE( newScore < 0 );
    REQUIRE( newScore == -CastlingEvaluator::defaultCastlingValue );
  }

  SECTION( "move rook on h to forfeit" )
  {
    REQUIRE( board.fromFEN("rnbqkbnr/1ppp1pp1/8/8/8/8/1PPP1PP1/1NBQKBNR") );
    // Score should be zero.
    const int score = evaluator.score(board);
    REQUIRE( score == 0 );
    REQUIRE( board.move(Field::h1, Field::h4, PieceType::queen) );
    REQUIRE_FALSE( board.castling().white_kingside );
    REQUIRE_FALSE( board.castling().white_queenside );
    REQUIRE( board.castling().white_castled == Ternary::false_value );
    // Score should be below zero, because black has advantage.
    const int newScore = evaluator.score(board);
    REQUIRE( newScore < 0 );
    REQUIRE( newScore == -CastlingEvaluator::defaultCastlingValue );
  }
}

TEST_CASE("CastlingEvaluator: black forfeits castling privileges")
{
  using namespace simplechess;
  Board board;
  CastlingEvaluator evaluator;

  SECTION( "move king to forfeit" )
  {
    REQUIRE( board.fromFEN("rnbqkbnr/1ppp1pp1/8/8/8/8/1PPP1PP1/RNBQKBNR b") );
    // Score should be zero.
    const int score = evaluator.score(board);
    REQUIRE( score == 0 );
    REQUIRE( board.move(Field::e8, Field::e7, PieceType::queen) );
    REQUIRE_FALSE( board.castling().black_kingside );
    REQUIRE_FALSE( board.castling().black_queenside );
    REQUIRE( board.castling().black_castled == Ternary::false_value );
    // Score should be above zero, because white has advantage.
    const int newScore = evaluator.score(board);
    REQUIRE( newScore > 0 );
    REQUIRE( newScore == CastlingEvaluator::defaultCastlingValue );
  }

  SECTION( "move rook on a to forfeit" )
  {
    REQUIRE( board.fromFEN("rnbqkbn1/1ppp1pp1/8/8/8/8/1PPP1PP1/RNBQKBNB b") );
    // Score should be zero.
    const int score = evaluator.score(board);
    REQUIRE( score == 0 );
    REQUIRE( board.move(Field::a8, Field::a5, PieceType::queen) );
    REQUIRE_FALSE( board.castling().black_kingside );
    REQUIRE_FALSE( board.castling().black_queenside );
    REQUIRE( board.castling().black_castled == Ternary::false_value );
    // Score should be above zero, because white has advantage.
    const int newScore = evaluator.score(board);
    REQUIRE( newScore > 0 );
    REQUIRE( newScore == CastlingEvaluator::defaultCastlingValue );
  }

  SECTION( "move rook on h to forfeit" )
  {
    REQUIRE( board.fromFEN("1nbqkbnr/1ppp1pp1/8/8/8/8/1PPP1PP1/RNBQKBNR b") );
    // Score should be zero.
    const int score = evaluator.score(board);
    REQUIRE( score == 0 );
    REQUIRE( board.move(Field::h8, Field::h7, PieceType::queen) );
    REQUIRE_FALSE( board.castling().black_kingside );
    REQUIRE_FALSE( board.castling().black_queenside );
    REQUIRE( board.castling().black_castled == Ternary::false_value );
    // Score should be above zero, because white has advantage.
    const int newScore = evaluator.score(board);
    REQUIRE( newScore > 0 );
    REQUIRE( newScore == CastlingEvaluator::defaultCastlingValue );
  }
}

TEST_CASE("CastlingEvaluator: white castles")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R") );

  CastlingEvaluator evaluator;
  // Evaluation should be zero - nobody has forfeited castling yet.
  REQUIRE(
      evaluator.score(board) == 0
  );

  SECTION( "kingside" )
  {
    REQUIRE( board.move(Field::e1, Field::g1, PieceType::queen) );
    REQUIRE_FALSE( board.castling().white_kingside );
    REQUIRE_FALSE( board.castling().white_queenside );
    REQUIRE( board.castling().white_castled == Ternary::true_value );
    // Score should be zero, because no malus occurs.
    const int newScore = evaluator.score(board);
    REQUIRE( newScore == 0 );
  }

  SECTION( "queenside" )
  {
    REQUIRE( board.move(Field::e1, Field::c1, PieceType::queen) );
    REQUIRE_FALSE( board.castling().white_kingside );
    REQUIRE_FALSE( board.castling().white_queenside );
    REQUIRE( board.castling().white_castled == Ternary::true_value );
    // Score should be zero, because no malus occurs.
    const int newScore = evaluator.score(board);
    REQUIRE( newScore == 0 );
  }
}

TEST_CASE("CastlingEvaluator: black castles")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R b") );

  CastlingEvaluator evaluator;
  // Evaluation should be zero - nobody has forfeited castling yet.
  REQUIRE(
      evaluator.score(board) == 0
  );

  SECTION( "kingside" )
  {
    REQUIRE( board.move(Field::e8, Field::g8, PieceType::queen) );
    REQUIRE_FALSE( board.castling().black_kingside );
    REQUIRE_FALSE( board.castling().black_queenside );
    REQUIRE( board.castling().black_castled == Ternary::true_value );
    // Score should be zero, because no malus occurs.
    const int newScore = evaluator.score(board);
    REQUIRE( newScore == 0 );
  }

  SECTION( "queenside" )
  {
    REQUIRE( board.move(Field::e8, Field::c8, PieceType::queen) );
    REQUIRE_FALSE( board.castling().black_kingside );
    REQUIRE_FALSE( board.castling().black_queenside );
    REQUIRE( board.castling().black_castled == Ternary::true_value );
    // Score should be zero, because no malus occurs.
    const int newScore = evaluator.score(board);
    REQUIRE( newScore == 0 );
  }
}
