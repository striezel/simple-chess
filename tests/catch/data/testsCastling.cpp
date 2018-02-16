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
#include "../../../data/Castling.hpp"

TEST_CASE("Castling:init")
{
  using namespace simplechess;
  Castling c;
  // all should be allowed by default
  REQUIRE( c.black_kingside );
  REQUIRE( c.black_queenside );
  REQUIRE( c.white_kingside );
  REQUIRE( c.white_queenside );
  // That also means that no side has castled yet.
  REQUIRE( c.white_castled == Ternary::false_value );
  REQUIRE( c.black_castled == Ternary::false_value );
}

TEST_CASE("Castling::fromFEN()")
{
  using namespace simplechess;
  Castling c;

  SECTION("-")
  {
    c.fromFEN("-");
    REQUIRE_FALSE( c.black_kingside );
    REQUIRE_FALSE( c.black_queenside );
    REQUIRE_FALSE( c.white_kingside );
    REQUIRE_FALSE( c.white_queenside );
    // Whether any side has castled is unknown.
    REQUIRE( c.white_castled == Ternary::maybe_value );
    REQUIRE( c.black_castled == Ternary::maybe_value );
  }

  SECTION("KQkq")
  {
    c.fromFEN("KQkq");
    REQUIRE( c.black_kingside );
    REQUIRE( c.black_queenside );
    REQUIRE( c.white_kingside );
    REQUIRE( c.white_queenside );
    // That implies that no side has castled yet.
    REQUIRE( c.white_castled == Ternary::false_value );
    REQUIRE( c.black_castled == Ternary::false_value );
  }

  SECTION("Kq")
  {
    c.fromFEN("Kq");
    REQUIRE_FALSE( c.black_kingside );
    REQUIRE( c.black_queenside );
    REQUIRE( c.white_kingside );
    REQUIRE_FALSE( c.white_queenside );
    // That implies that no side has castled yet.
    REQUIRE( c.white_castled == Ternary::false_value );
    REQUIRE( c.black_castled == Ternary::false_value );
  }

  SECTION("Qk")
  {
    c.fromFEN("Qk");
    REQUIRE( c.black_kingside );
    REQUIRE_FALSE( c.black_queenside );
    REQUIRE_FALSE( c.white_kingside );
    REQUIRE( c.white_queenside );
    // That implies that no side has castled yet.
    REQUIRE( c.white_castled == Ternary::false_value );
    REQUIRE( c.black_castled == Ternary::false_value );
  }
}


TEST_CASE("Castling::toFEN()")
{
  using namespace simplechess;
  Castling c;

  SECTION("-")
  {
    c.black_kingside = false;
    c.black_queenside = false;
    c.white_kingside = false;
    c.white_queenside = false;
    REQUIRE( c.toFEN() == "-" );
  }

  SECTION("KQkq")
  {
    REQUIRE( c.toFEN() == "KQkq" );
  }

  SECTION("Kq")
  {
    c.black_kingside = false;
    c.white_queenside = false;
    REQUIRE( c.toFEN() == "Kq" );
  }

  SECTION("Qk")
  {
    c.black_queenside = false;
    c.white_kingside = false;
    REQUIRE( c.toFEN() == "Qk" );
  }
}
