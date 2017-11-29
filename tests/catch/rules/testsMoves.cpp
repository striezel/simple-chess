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
#include "../../../rules/Moves.hpp"

TEST_CASE("Moves::sanitizePromotion() test")
{
  using namespace simplechess;
  // "none" is not allowed and should be changed during sanitization.
  PieceType pt = PieceType::none;
  Moves::sanitizePromotion(pt);
  REQUIRE( pt != PieceType::none );
  // Fallback is queen.
  REQUIRE( pt == PieceType::queen );

  // Pawn is not allowed and should be changed during sanitization.
  pt = PieceType::pawn;
  Moves::sanitizePromotion(pt);
  REQUIRE( pt != PieceType::pawn );
  // Fallback is queen.
  REQUIRE( pt == PieceType::queen );

  // Rook is allowed and should not be changed during sanitization.
  pt = PieceType::rook;
  Moves::sanitizePromotion(pt);
  REQUIRE( pt == PieceType::rook );

  // Knight is allowed and should not be changed during sanitization.
  pt = PieceType::knight;
  Moves::sanitizePromotion(pt);
  REQUIRE( pt == PieceType::knight );

  // Bishop is allowed and should not be changed during sanitization.
  pt = PieceType::bishop;
  Moves::sanitizePromotion(pt);
  REQUIRE( pt == PieceType::bishop );

  // Queen is allowed and should not be changed during sanitization.
  pt = PieceType::queen;
  Moves::sanitizePromotion(pt);
  REQUIRE( pt == PieceType::queen );

  // King is not allowed and should be changed during sanitization.
  pt = PieceType::king;
  Moves::sanitizePromotion(pt);
  REQUIRE( pt != PieceType::king );
  // Fallback is queen.
  REQUIRE( pt == PieceType::queen );
}

TEST_CASE("Moves::allowed(): rook")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("8/8/8/8/8/8/8/R7") );

  SECTION( "allowed rook moves" )
  {
    REQUIRE( Moves::allowed(board, Field::a1, Field::a2) );
    REQUIRE( Moves::allowed(board, Field::a1, Field::a3) );
    REQUIRE( Moves::allowed(board, Field::a1, Field::a4) );
    REQUIRE( Moves::allowed(board, Field::a1, Field::a5) );
    REQUIRE( Moves::allowed(board, Field::a1, Field::a6) );
    REQUIRE( Moves::allowed(board, Field::a1, Field::a7) );
    REQUIRE( Moves::allowed(board, Field::a1, Field::a8) );

    REQUIRE( Moves::allowed(board, Field::a1, Field::b1) );
    REQUIRE( Moves::allowed(board, Field::a1, Field::c1) );
    REQUIRE( Moves::allowed(board, Field::a1, Field::d1) );
    REQUIRE( Moves::allowed(board, Field::a1, Field::e1) );
    REQUIRE( Moves::allowed(board, Field::a1, Field::f1) );
    REQUIRE( Moves::allowed(board, Field::a1, Field::g1) );
    REQUIRE( Moves::allowed(board, Field::a1, Field::h1) );
  }

  SECTION( "illegal rook moves" )
  {
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::a1) );

    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::b2) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::b3) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::b4) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::b5) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::b6) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::b7) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::b8) );

    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::c2) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::c3) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::c4) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::c5) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::c6) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::c7) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::c8) );

    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::d2) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::d3) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::d4) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::d5) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::d6) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::d7) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::d8) );

    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::e2) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::e3) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::e4) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::e5) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::e6) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::e7) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::e8) );

    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::f2) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::f3) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::f4) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::f5) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::f6) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::f7) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::f8) );

    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::g2) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::g3) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::g4) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::g5) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::g6) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::g7) );
    REQUIRE_FALSE( Moves::allowed(board, Field::a1, Field::g8) );
  }
}

TEST_CASE("Moves::allowed(): king")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("8/8/8/8/8/8/8/R3K2R") );

  SECTION( "allowed normal king moves" )
  {
    REQUIRE( Moves::allowed(board, Field::e1, Field::d1) );
    REQUIRE( Moves::allowed(board, Field::e1, Field::d2) );
    REQUIRE( Moves::allowed(board, Field::e1, Field::e2) );
    REQUIRE( Moves::allowed(board, Field::e1, Field::f2) );
    REQUIRE( Moves::allowed(board, Field::e1, Field::f1) );
  }

  SECTION( "allowed castling moves" )
  {
    REQUIRE( Moves::allowed(board, Field::e1, Field::c1) );
    REQUIRE( Moves::allowed(board, Field::e1, Field::g1) );
  }

  SECTION( "illegal king moves" )
  {
    // Only test some disallowed moves.
    REQUIRE_FALSE( Moves::allowed(board, Field::e1, Field::e1) );

    REQUIRE_FALSE( Moves::allowed(board, Field::e1, Field::a1) );
    REQUIRE_FALSE( Moves::allowed(board, Field::e1, Field::b1) );
    REQUIRE_FALSE( Moves::allowed(board, Field::e1, Field::c2) );
    REQUIRE_FALSE( Moves::allowed(board, Field::e1, Field::d3) );
    REQUIRE_FALSE( Moves::allowed(board, Field::e1, Field::e3) );
    REQUIRE_FALSE( Moves::allowed(board, Field::e1, Field::f3) );
    REQUIRE_FALSE( Moves::allowed(board, Field::e1, Field::g2) );
    REQUIRE_FALSE( Moves::allowed(board, Field::e1, Field::h1) );
  }
}
