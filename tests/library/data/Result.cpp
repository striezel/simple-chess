/*
 -------------------------------------------------------------------------------
    This file is part of the test suite for simple-chess.
    Copyright (C) 2017, 2018, 2021  Dirk Stolle

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
#include "../../../libsimple-chess/data/Result.hpp"

TEST_CASE("Result: resultToString")
{
  using namespace simplechess;

  REQUIRE( resultToString(Result::Unknown) == "*" );
  REQUIRE( resultToString(Result::WhiteWins) == "1-0" );
  REQUIRE( resultToString(Result::BlackWins) == "0-1" );
  REQUIRE( resultToString(Result::Draw) == "1/2-1/2" );
}

TEST_CASE("Result: stringToResult")
{
  using namespace simplechess;

  REQUIRE( stringToResult("*") == Result::Unknown );
  REQUIRE( stringToResult("1-0") == Result::WhiteWins );
  REQUIRE( stringToResult("0-1") == Result::BlackWins );
  REQUIRE( stringToResult("1/2-1/2") == Result::Draw );

  REQUIRE( stringToResult("foo") == Result::Unknown );
}

TEST_CASE("Result: stringToResult-resultToString round-trip")
{
  using namespace simplechess;

  REQUIRE( stringToResult(resultToString(Result::Unknown)) == Result::Unknown );
  REQUIRE( stringToResult(resultToString(Result::WhiteWins)) == Result::WhiteWins );
  REQUIRE( stringToResult(resultToString(Result::BlackWins)) == Result::BlackWins );
  REQUIRE( stringToResult(resultToString(Result::Draw)) == Result::Draw );
}
