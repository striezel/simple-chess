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
#include "../../../rules/check.hpp"
#include "../../../rules/Moves.hpp"

TEST_CASE("isUnderAttack() test")
{
  using namespace simplechess;
  Board board;

  SECTION( "simple position with knights" )
  {
    REQUIRE(board.fromFEN("4k3/8/4n3/8/8/4N3/8/4K3"));

    // White knight attacks d1, f1, g2, g4, f5, d5, c4, c2.
    REQUIRE( isUnderAttack(board, Colour::white, Field::d1) );
    REQUIRE( isUnderAttack(board, Colour::white, Field::f1) );
    REQUIRE( isUnderAttack(board, Colour::white, Field::g2) );
    REQUIRE( isUnderAttack(board, Colour::white, Field::g4) );
    REQUIRE( isUnderAttack(board, Colour::white, Field::f5) );
    REQUIRE( isUnderAttack(board, Colour::white, Field::d5) );
    REQUIRE( isUnderAttack(board, Colour::white, Field::c4) );
    REQUIRE( isUnderAttack(board, Colour::white, Field::c2) );

    // White king attacks d1, d2, e2, f2, f1.
    REQUIRE( isUnderAttack(board, Colour::white, Field::d1) );
    REQUIRE( isUnderAttack(board, Colour::white, Field::d2) );
    REQUIRE( isUnderAttack(board, Colour::white, Field::e2) );
    REQUIRE( isUnderAttack(board, Colour::white, Field::f2) );
    REQUIRE( isUnderAttack(board, Colour::white, Field::f1) );

    // Whole a and b files are not attacked.
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::a1) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::a2) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::a3) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::a4) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::a5) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::a6) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::a7) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::a8) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::b1) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::b2) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::b3) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::b4) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::b5) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::b6) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::b7) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::b8) );
    // Some fields on file c are not attacked.
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::c1) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::c3) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::c5) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::c6) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::c7) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::c8) );
    // Some fields on file d are not attacked.
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::d3) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::d4) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::d6) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::d7) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::d8) );
    // Some fields on file e are not attacked.
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::e3) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::e4) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::e5) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::e6) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::e7) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::e8) );
    // Some fields on file f are not attacked.
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::f3) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::f4) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::f6) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::f7) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::f8) );
    // Some fields on file g are not attacked.
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::g1) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::g3) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::g5) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::g6) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::g7) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::g8) );
    // Whole h file is not attacked.
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::h1) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::h2) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::h3) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::h4) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::h5) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::h6) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::h7) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::white, Field::h8) );

    // Black knight attacks d8, c7, c5, d4, f4, g5, g7, f8.
    REQUIRE( isUnderAttack(board, Colour::black, Field::d8) );
    REQUIRE( isUnderAttack(board, Colour::black, Field::c7) );
    REQUIRE( isUnderAttack(board, Colour::black, Field::c5) );
    REQUIRE( isUnderAttack(board, Colour::black, Field::d4) );
    REQUIRE( isUnderAttack(board, Colour::black, Field::f4) );
    REQUIRE( isUnderAttack(board, Colour::black, Field::g5) );
    REQUIRE( isUnderAttack(board, Colour::black, Field::g7) );
    REQUIRE( isUnderAttack(board, Colour::black, Field::f8) );

    // Black king attacks d8, d7, e7, f7, f8.
    REQUIRE( isUnderAttack(board, Colour::black, Field::d8) );
    REQUIRE( isUnderAttack(board, Colour::black, Field::d7) );
    REQUIRE( isUnderAttack(board, Colour::black, Field::e7) );
    REQUIRE( isUnderAttack(board, Colour::black, Field::f7) );
    REQUIRE( isUnderAttack(board, Colour::black, Field::f8) );

    // Whole a and b files are not attacked.
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::a1) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::a2) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::a3) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::a4) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::a5) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::a6) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::a7) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::a8) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::b1) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::b2) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::b3) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::b4) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::b5) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::b6) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::b7) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::b8) );
    // Some fields on file c are not attacked.
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::c1) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::c2) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::c3) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::c4) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::c6) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::c8) );
    // Some fields on file d are not attacked.
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::d1) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::d2) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::d3) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::d5) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::d6) );
    // Some fields on file e are not attacked.
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::e1) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::e2) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::e3) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::e4) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::e5) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::e6) );
    // Some fields on file g are not attacked.
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::g1) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::g2) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::g3) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::g4) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::g6) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::g8) );
    // Whole h file is not attacked.
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::h1) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::h2) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::h3) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::h4) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::h5) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::h6) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::h7) );
    REQUIRE_FALSE( isUnderAttack(board, Colour::black, Field::h8) );
  }

  SECTION( "two opposing pawns" )
  {
    REQUIRE(board.fromFEN("4k3/8/8/3p4/4P3/8/8/4K3"));

    // White pawn attacks d5 and e5.
    REQUIRE( isUnderAttack(board, Colour::white, Field::d5) );
    REQUIRE( isUnderAttack(board, Colour::white, Field::e5) );

    // Black pawn attacks d4 and e4.
    REQUIRE( isUnderAttack(board, Colour::black, Field::d4) );
    REQUIRE( isUnderAttack(board, Colour::black, Field::e4) );
  }
}

TEST_CASE("isInCheck() test")
{
  using namespace simplechess;
  Board board;

  SECTION( "default start position" )
  {
    REQUIRE(board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"));
    // Nobody is in check yet.
    REQUIRE_FALSE( isInCheck(board, Colour::white) );
    REQUIRE_FALSE( isInCheck(board, Colour::black) );

    board.setToMove(Colour::black);
    REQUIRE_FALSE( isInCheck(board, Colour::white) );
    REQUIRE_FALSE( isInCheck(board, Colour::black) );
  }

  SECTION( "white in check but not checkmate" )
  {
    REQUIRE(board.fromFEN("rnb1kbnr/ppppqppp/8/8/8/8/PPPP1PPP/RNBQKBNR"));
    // White is in check.
    REQUIRE( isInCheck(board, Colour::white) );
    REQUIRE_FALSE( isInCheck(board, Colour::black) );

    board.setToMove(Colour::black);
    REQUIRE( isInCheck(board, Colour::white) );
    REQUIRE_FALSE( isInCheck(board, Colour::black) );
  }

  SECTION( "black in check but not checkmate" )
  {
    REQUIRE(board.fromFEN("rnbqkbnr/pppp1ppp/8/8/8/8/PPPPQPPP/RNB1KBNR"));
    // Black is in check.
    REQUIRE_FALSE( isInCheck(board, Colour::white) );
    REQUIRE( isInCheck(board, Colour::black) );

    board.setToMove(Colour::black);
    REQUIRE_FALSE( isInCheck(board, Colour::white) );
    REQUIRE( isInCheck(board, Colour::black) );
  }

  SECTION( "white is checkmate" )
  {
    REQUIRE(board.fromFEN("8/8/8/8/8/4r3/4q3/4K3"));
    // White is checkmate, and thus in check, too.
    REQUIRE( isInCheck(board, Colour::white) );
    REQUIRE_FALSE( isInCheck(board, Colour::black) );
  }

  SECTION( "black is checkmate" )
  {
    REQUIRE(board.fromFEN("8/8/8/8/8/4K3/4Q3/4k3 b"));
    // Black is checkmate, and thus in check, too.
    REQUIRE_FALSE( isInCheck(board, Colour::white) );
    REQUIRE( isInCheck(board, Colour::black) );
  }
}

TEST_CASE("isInCheck(): test scenario with black in check")
{
  // This is a regression test for a scenario that occurred when the cli was
  // started with the position given below and black to move. Instead of moving
  // the black king out of check, the engine moved a pawn from c2 to c1.
  using namespace simplechess;
  Board board;

  // Position where black is in check, because white queen attacks black king.
  REQUIRE(board.fromFEN("rnb2bnN/ppp1k1pp/8/3BQ3/4P3/8/PPp2PPP/RN2K2R b"));
  // White player is not in check.
  REQUIRE_FALSE( isInCheck(board, Colour::white) );
  REQUIRE_FALSE( board.isInCheck(Colour::white) );
  // Black player is in check.
  REQUIRE( isInCheck(board, Colour::black) );
  REQUIRE( board.isInCheck(Colour::black) );
  // Move from c2 to c1 is not allowed, because king is still in check.
  REQUIRE_FALSE( Moves::isAllowed(board, Field::c2, Field::c1)  );
  REQUIRE_FALSE( board.move(Field::c2, Field::c1, PieceType::queen) );

  // White player is not in check.
  board.setToMove(Colour::white);
  REQUIRE_FALSE( isInCheck(board, Colour::white) );
  REQUIRE( isInCheck(board, Colour::black) );
}


TEST_CASE("isCheckMate() test")
{
  using namespace simplechess;
  Board board;

  SECTION( "default start position" )
  {
    REQUIRE(board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"));
    // Nobody is checkmate yet.
    REQUIRE_FALSE( isCheckMate(board, Colour::white) );
    REQUIRE_FALSE( isCheckMate(board, Colour::black) );

    board.setToMove(Colour::black);
    REQUIRE_FALSE( isCheckMate(board, Colour::white) );
    REQUIRE_FALSE( isCheckMate(board, Colour::black) );
  }

  SECTION( "white in check but not checkmate" )
  {
    REQUIRE(board.fromFEN("rnb1kbnr/ppppqppp/8/8/8/8/PPPP1PPP/RNBQKBNR"));
    // Nobody is checkmate yet.
    REQUIRE_FALSE( isCheckMate(board, Colour::white) );
    REQUIRE_FALSE( isCheckMate(board, Colour::black) );

    board.setToMove(Colour::black);
    REQUIRE_FALSE( isCheckMate(board, Colour::white) );
    REQUIRE_FALSE( isCheckMate(board, Colour::black) );
  }

  SECTION( "black in check but not checkmate" )
  {
    REQUIRE(board.fromFEN("rnbqkbnr/pppp1ppp/8/8/8/8/PPPPQPPP/RNB1KBNR"));
    // Nobody is checkmate yet.
    REQUIRE_FALSE( isCheckMate(board, Colour::white) );
    REQUIRE_FALSE( isCheckMate(board, Colour::black) );

    board.setToMove(Colour::black);
    REQUIRE_FALSE( isCheckMate(board, Colour::white) );
    REQUIRE_FALSE( isCheckMate(board, Colour::black) );
  }

  SECTION( "white is checkmate" )
  {
    REQUIRE(board.fromFEN("8/8/8/8/8/4r3/4q3/4K3"));
    // White is checkmate.
    REQUIRE( isCheckMate(board, Colour::white) );
    REQUIRE_FALSE( isCheckMate(board, Colour::black) );
  }

  SECTION( "black is checkmate" )
  {
    REQUIRE(board.fromFEN("8/8/8/8/8/4K3/4Q3/4k3 b"));
    // Black is checkmate.
    REQUIRE_FALSE( isCheckMate(board, Colour::white) );
    REQUIRE( isCheckMate(board, Colour::black) );
  }
}
