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
#include "../../../util/strings.hpp"

TEST_CASE("split()")
{
  using namespace simplechess::util;
  const std::string text = "This is a test.";


  SECTION("split at space character")
  {
    const auto pieces = split(text);
    REQUIRE( pieces.size() == 4 );
    REQUIRE( pieces.at(0) == "This" );
    REQUIRE( pieces.at(1) == "is" );
    REQUIRE( pieces.at(2) == "a" );
    REQUIRE( pieces.at(3) == "test." );
  }

  SECTION("split at 'i'")
  {
    const auto pieces = split(text, 'i');
    REQUIRE( pieces.size() == 3 );
    REQUIRE( pieces.at(0) == "Th" );
    REQUIRE( pieces.at(1) == "s " );
    REQUIRE( pieces.at(2) == "s a test." );
  }

  SECTION("split at non-existent character")
  {
    const auto pieces = split(text, 'Z');
    REQUIRE( pieces.size() == 1 );
    REQUIRE( pieces.at(0) == text );
  }

  SECTION("split empty string")
  {
    const auto pieces = split("");
    REQUIRE( pieces.size() == 1 );
    REQUIRE( pieces.at(0) == "" );
  }
}

TEST_CASE("intToString()")
{
  using namespace simplechess::util;

  REQUIRE( intToString(0) == "0" );
  REQUIRE( intToString(1) == "1" );
  REQUIRE( intToString(1234567890) == "1234567890" );
  REQUIRE( intToString(-123456789) == "-123456789" );
}

TEST_CASE("stringToInt()")
{
  using namespace simplechess::util;

  int out = -1;
  REQUIRE( stringToInt("0", out) );
  REQUIRE( out == 0 );

  REQUIRE( stringToInt("1", out) );
  REQUIRE( out == 1 );

  REQUIRE( stringToInt("56789", out) );
  REQUIRE( out == 56789 );

  REQUIRE( stringToInt("-17348", out) );
  REQUIRE( out == -17348 );

  REQUIRE_FALSE( stringToInt("hey1", out) );
  REQUIRE_FALSE( stringToInt("1.2", out) );
  REQUIRE_FALSE( stringToInt("not an integer!", out) );
  REQUIRE_FALSE( stringToInt("123 and still not an integer!", out) );
}

TEST_CASE("trimLeft()")
{
  using namespace simplechess::util;
  std::string text;

  text = "";
  trimLeft(text);
  REQUIRE( text == "" );

  text = "    \t \r\n\n\r \v   ";
  trimLeft(text);
  REQUIRE( text == "" );

  text = "    \r\nthis";
  trimLeft(text);
  REQUIRE( text == "this" );

  text = "    \r\nthis    ";
  trimLeft(text);
  REQUIRE( text == "this    " );

  text = "\ntext";
  trimLeft(text);
  REQUIRE( text == "text" );
}
