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


#include <catch.hpp>
#include "../../../rules/Moves.hpp"

TEST_CASE("Moves::sanitizePromotion() test")
{
  using namespace simplechess;
  // "none" is not allowed and should be changed during sanitation.
  PieceType pt = PieceType::none;
  Moves::sanitizePromotion(pt);
  REQUIRE( pt != PieceType::none );
  // Fallback is queen.
  REQUIRE( pt == PieceType::queen );

  // Pawn is not allowed and should be changed during sanitation.
  pt = PieceType::pawn;
  Moves::sanitizePromotion(pt);
  REQUIRE( pt != PieceType::pawn );
  // Fallback is queen.
  REQUIRE( pt == PieceType::queen );

  // Rook is allowed and should not be changed during sanitation.
  pt = PieceType::rook;
  Moves::sanitizePromotion(pt);
  REQUIRE( pt == PieceType::rook );

  // Knight is allowed and should not be changed during sanitation.
  pt = PieceType::knight;
  Moves::sanitizePromotion(pt);
  REQUIRE( pt == PieceType::knight );

  // Bishop is allowed and should not be changed during sanitation.
  pt = PieceType::bishop;
  Moves::sanitizePromotion(pt);
  REQUIRE( pt == PieceType::bishop );

  // Queen is allowed and should not be changed during sanitation.
  pt = PieceType::queen;
  Moves::sanitizePromotion(pt);
  REQUIRE( pt == PieceType::queen );

  // King is not allowed and should be changed during sanitation.
  pt = PieceType::king;
  Moves::sanitizePromotion(pt);
  REQUIRE( pt != PieceType::king );
  // Fallback is queen.
  REQUIRE( pt == PieceType::queen );
}

TEST_CASE("Moves::isAllowed(): rook")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("8/8/8/8/8/8/8/R7") );

  SECTION( "allowed rook moves" )
  {
    REQUIRE( Moves::isAllowed(board, Field::a1, Field::a2) );
    REQUIRE( Moves::isAllowed(board, Field::a1, Field::a3) );
    REQUIRE( Moves::isAllowed(board, Field::a1, Field::a4) );
    REQUIRE( Moves::isAllowed(board, Field::a1, Field::a5) );
    REQUIRE( Moves::isAllowed(board, Field::a1, Field::a6) );
    REQUIRE( Moves::isAllowed(board, Field::a1, Field::a7) );
    REQUIRE( Moves::isAllowed(board, Field::a1, Field::a8) );

    REQUIRE( Moves::isAllowed(board, Field::a1, Field::b1) );
    REQUIRE( Moves::isAllowed(board, Field::a1, Field::c1) );
    REQUIRE( Moves::isAllowed(board, Field::a1, Field::d1) );
    REQUIRE( Moves::isAllowed(board, Field::a1, Field::e1) );
    REQUIRE( Moves::isAllowed(board, Field::a1, Field::f1) );
    REQUIRE( Moves::isAllowed(board, Field::a1, Field::g1) );
    REQUIRE( Moves::isAllowed(board, Field::a1, Field::h1) );
  }

  SECTION( "illegal rook moves" )
  {
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::a1) );

    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::b2) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::b3) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::b4) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::b5) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::b6) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::b7) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::b8) );

    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::c2) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::c3) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::c4) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::c5) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::c6) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::c7) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::c8) );

    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::d2) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::d3) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::d4) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::d5) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::d6) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::d7) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::d8) );

    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::e2) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::e3) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::e4) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::e5) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::e6) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::e7) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::e8) );

    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::f2) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::f3) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::f4) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::f5) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::f6) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::f7) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::f8) );

    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::g2) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::g3) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::g4) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::g5) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::g6) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::g7) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::a1, Field::g8) );
  }
}

TEST_CASE("Moves::isAllowed(): king")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("8/8/8/8/8/8/8/R3K2R") );

  SECTION( "allowed normal king moves" )
  {
    REQUIRE( Moves::isAllowed(board, Field::e1, Field::d1) );
    REQUIRE( Moves::isAllowed(board, Field::e1, Field::d2) );
    REQUIRE( Moves::isAllowed(board, Field::e1, Field::e2) );
    REQUIRE( Moves::isAllowed(board, Field::e1, Field::f2) );
    REQUIRE( Moves::isAllowed(board, Field::e1, Field::f1) );
  }

  SECTION( "allowed castling moves" )
  {
    REQUIRE( Moves::isAllowed(board, Field::e1, Field::c1) );
    REQUIRE( Moves::isAllowed(board, Field::e1, Field::g1) );
  }

  SECTION( "illegal king moves" )
  {
    // Only test some disallowed moves.
    REQUIRE_FALSE( Moves::isAllowed(board, Field::e1, Field::e1) );

    REQUIRE_FALSE( Moves::isAllowed(board, Field::e1, Field::a1) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::e1, Field::b1) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::e1, Field::c2) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::e1, Field::d3) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::e1, Field::e3) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::e1, Field::f3) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::e1, Field::g2) );
    REQUIRE_FALSE( Moves::isAllowed(board, Field::e1, Field::h1) );
  }
}

TEST_CASE("Moves::isAllowed(): player may not put himself/herself into check")
{
  using namespace simplechess;
  Board board;
  REQUIRE( board.fromFEN("k7/8/8/8/8/8/r7/4K3") );

  // Usual fields in row 1 are allowed.
  REQUIRE( Moves::isAllowed(board, Field::e1, Field::d1) );
  REQUIRE( Moves::isAllowed(board, Field::e1, Field::f1) );

  // Fields in row 2 are all forbidden, because of check by rook.
  REQUIRE_FALSE( Moves::isAllowed(board, Field::e1, Field::d2) );
  REQUIRE_FALSE( Moves::isAllowed(board, Field::e1, Field::e2) );
  REQUIRE_FALSE( Moves::isAllowed(board, Field::e1, Field::f2) );
}

TEST_CASE("Moves::isPromotion() test")
{
  using namespace simplechess;
  Board board;

  SECTION( "promotable white pawn" )
  {
    REQUIRE( board.fromFEN("8/pPpppppp/8/8/8/8/8/8") );
    REQUIRE( Moves::isPromotion(board, Field::b7, Field::b8) );
  }

  SECTION( "promotable white pawn" )
  {
    REQUIRE( board.fromFEN("8/8/8/8/8/8/PpPPPPPP/8") );
    REQUIRE( Moves::isPromotion(board, Field::b2, Field::b1) );
  }

  SECTION( "start position - no promotions" )
  {
    REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR") );
    REQUIRE_FALSE( Moves::isPromotion(board, Field::a2, Field::a3) );
    REQUIRE_FALSE( Moves::isPromotion(board, Field::b2, Field::b3) );
    REQUIRE_FALSE( Moves::isPromotion(board, Field::c2, Field::c3) );
    REQUIRE_FALSE( Moves::isPromotion(board, Field::d2, Field::d3) );
    REQUIRE_FALSE( Moves::isPromotion(board, Field::e2, Field::e3) );
    REQUIRE_FALSE( Moves::isPromotion(board, Field::f2, Field::f3) );
    REQUIRE_FALSE( Moves::isPromotion(board, Field::g2, Field::g3) );
    REQUIRE_FALSE( Moves::isPromotion(board, Field::h2, Field::h3) );

    REQUIRE_FALSE( Moves::isPromotion(board, Field::a7, Field::a6) );
    REQUIRE_FALSE( Moves::isPromotion(board, Field::b7, Field::b6) );
    REQUIRE_FALSE( Moves::isPromotion(board, Field::c7, Field::c6) );
    REQUIRE_FALSE( Moves::isPromotion(board, Field::d7, Field::d6) );
    REQUIRE_FALSE( Moves::isPromotion(board, Field::e7, Field::e6) );
    REQUIRE_FALSE( Moves::isPromotion(board, Field::f7, Field::f6) );
    REQUIRE_FALSE( Moves::isPromotion(board, Field::g7, Field::g6) );
    REQUIRE_FALSE( Moves::isPromotion(board, Field::h7, Field::h6) );
  }
}
