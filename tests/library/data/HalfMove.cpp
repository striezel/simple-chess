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

#include "../../locate_catch.hpp"
#include "../../../libsimple-chess/data/HalfMove.hpp"

TEST_CASE("HalfMove::empty()")
{
  using namespace simplechess;

  HalfMove hm;
  REQUIRE( hm.empty() );

  hm = HalfMove(PieceType::knight, Field::d3, Field::e1, true);
  REQUIRE_FALSE( hm.empty() );
}

TEST_CASE("HalfMove::fromPGN()")
{
  using namespace simplechess;
  HalfMove hm;

  SECTION("e4")
  {
    REQUIRE( hm.fromPGN("e4") );
    REQUIRE( hm.piece() == PieceType::pawn );
    REQUIRE( hm.origin() == Field::none );
    REQUIRE( hm.destination() == Field::e4 );
    REQUIRE_FALSE( hm.capture() );
    REQUIRE_FALSE( hm.check() );
    REQUIRE_FALSE( hm.checkmate() );
    REQUIRE_FALSE( hm.kingsideCastling() );
    REQUIRE_FALSE( hm.queensideCastling() );
  }

  SECTION("Pe2xf3")
  {
    // Specifying P for pawn is allowed in some variations, although the piece
    // is usually omitted for pawns.
    REQUIRE( hm.fromPGN("Pe2xf3") );
    REQUIRE( hm.piece() == PieceType::pawn );
    REQUIRE( hm.origin() == Field::e2 );
    REQUIRE( hm.destination() == Field::f3 );
    REQUIRE( hm.capture() );
    REQUIRE_FALSE( hm.check() );
    REQUIRE_FALSE( hm.checkmate() );
    REQUIRE_FALSE( hm.kingsideCastling() );
    REQUIRE_FALSE( hm.queensideCastling() );
  }

  SECTION("Bd3xe4+")
  {
    REQUIRE( hm.fromPGN("Bd3xe4+") );
    REQUIRE( hm.piece() == PieceType::bishop );
    REQUIRE( hm.origin() == Field::d3 );
    REQUIRE( hm.destination() == Field::e4 );
    REQUIRE( hm.capture() );
    REQUIRE( hm.check() );
    REQUIRE_FALSE( hm.checkmate() );
    REQUIRE_FALSE( hm.kingsideCastling() );
    REQUIRE_FALSE( hm.queensideCastling() );
  }

  SECTION("Bd3xe4#")
  {
    REQUIRE( hm.fromPGN("Bd3xe4#") );
    REQUIRE( hm.piece() == PieceType::bishop );
    REQUIRE( hm.origin() == Field::d3 );
    REQUIRE( hm.destination() == Field::e4 );
    REQUIRE( hm.capture() );
    REQUIRE_FALSE( hm.check() );
    REQUIRE( hm.checkmate() );
    REQUIRE_FALSE( hm.kingsideCastling() );
    REQUIRE_FALSE( hm.queensideCastling() );
  }

  SECTION("O-O")
  {
    REQUIRE( hm.fromPGN("O-O") );
    REQUIRE( hm.piece() == PieceType::king );
    REQUIRE( hm.origin() == Field::none );
    REQUIRE( hm.destination() == Field::none );
    REQUIRE_FALSE( hm.capture() );
    REQUIRE_FALSE( hm.check() );
    REQUIRE( hm.kingsideCastling() );
    REQUIRE_FALSE( hm.queensideCastling() );
  }

  SECTION("O-O-O")
  {
    REQUIRE( hm.fromPGN("O-O-O") );
    REQUIRE( hm.piece() == PieceType::king );
    REQUIRE( hm.origin() == Field::none );
    REQUIRE( hm.destination() == Field::none );
    REQUIRE_FALSE( hm.capture() );
    REQUIRE_FALSE( hm.check() );
    REQUIRE_FALSE( hm.checkmate() );
    REQUIRE_FALSE( hm.kingsideCastling() );
    REQUIRE( hm.queensideCastling() );
  }

  SECTION("empty")
  {
    REQUIRE_FALSE( hm.fromPGN("") );
  }

  SECTION("invalid notation")
  {
    REQUIRE_FALSE( hm.fromPGN("Ja2xb3") );
  }
}

TEST_CASE("HalfMove::toPGN()")
{
  using namespace simplechess;
  HalfMove hm;

  SECTION("e4")
  {
    HalfMove hm(PieceType::pawn, Field::e4, false);
    REQUIRE( hm.toPGN() == "e4" );
  }

  SECTION("Nxb8")
  {
    HalfMove hm(PieceType::knight, Field::b8, true);
    REQUIRE( hm.toPGN() == "Nxb8" );
  }

  SECTION("N6b8+")
  {
    REQUIRE( hm.fromPGN("N6b8+") );
    REQUIRE( hm.toPGN() == "N6b8+" );
  }

  SECTION("Qd6xf8+")
  {
    REQUIRE( hm.fromPGN("Qd6xf8+") );
    REQUIRE( hm.toPGN() == "Qd6xf8+" );
    REQUIRE( hm.check() );
    REQUIRE_FALSE( hm.checkmate() );
  }

  SECTION("Qd6xf8#")
  {
    REQUIRE( hm.fromPGN("Qd6xf8#") );
    REQUIRE( hm.toPGN() == "Qd6xf8#" );
    REQUIRE_FALSE( hm.check() );
    REQUIRE( hm.checkmate() );
  }

  SECTION("O-O")
  {
    REQUIRE( hm.fromPGN("O-O") );
    REQUIRE( hm.toPGN() == "O-O" );
  }

  SECTION("O-O-O")
  {
    REQUIRE( hm.fromPGN("O-O-O") );
    REQUIRE( hm.toPGN() == "O-O-O" );
  }

  SECTION("empty")
  {
    REQUIRE( hm.toPGN().empty() );
  }
}
