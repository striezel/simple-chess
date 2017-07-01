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
#include "../../../data/Field.hpp"

TEST_CASE("Field: column()")
{
  using namespace simplechess;

  REQUIRE( column(Field::a1) == 'a' );
  REQUIRE( column(Field::a2) == 'a' );
  REQUIRE( column(Field::a3) == 'a' );
  REQUIRE( column(Field::a4) == 'a' );
  REQUIRE( column(Field::a5) == 'a' );
  REQUIRE( column(Field::a6) == 'a' );
  REQUIRE( column(Field::a7) == 'a' );
  REQUIRE( column(Field::a8) == 'a' );
  REQUIRE( column(Field::b1) == 'b' );
  REQUIRE( column(Field::b8) == 'b' );
  REQUIRE( column(Field::c1) == 'c' );
  REQUIRE( column(Field::c8) == 'c' );
  REQUIRE( column(Field::d1) == 'd' );
  REQUIRE( column(Field::d8) == 'd' );
  REQUIRE( column(Field::e1) == 'e' );
  REQUIRE( column(Field::e8) == 'e' );
  REQUIRE( column(Field::f1) == 'f' );
  REQUIRE( column(Field::f8) == 'f' );
  REQUIRE( column(Field::g1) == 'g' );
  REQUIRE( column(Field::g8) == 'g' );
  REQUIRE( column(Field::h1) == 'h' );
  REQUIRE( column(Field::h8) == 'h' );

  REQUIRE_THROWS( column(Field::none) );
}

TEST_CASE("Field: row()")
{
  using namespace simplechess;

  REQUIRE( row(Field::a1) == 1 );
  REQUIRE( row(Field::b1) == 1 );
  REQUIRE( row(Field::c1) == 1 );
  REQUIRE( row(Field::d1) == 1 );
  REQUIRE( row(Field::e1) == 1 );
  REQUIRE( row(Field::f1) == 1 );
  REQUIRE( row(Field::g1) == 1 );
  REQUIRE( row(Field::h1) == 1 );

  REQUIRE( row(Field::a2) == 2 );
  REQUIRE( row(Field::a3) == 3 );
  REQUIRE( row(Field::a4) == 4 );
  REQUIRE( row(Field::a5) == 5 );
  REQUIRE( row(Field::a6) == 6 );
  REQUIRE( row(Field::a7) == 7 );
  REQUIRE( row(Field::a8) == 8 );

  REQUIRE( row(Field::a8) == 8 );
  REQUIRE( row(Field::b8) == 8 );
  REQUIRE( row(Field::c8) == 8 );
  REQUIRE( row(Field::d8) == 8 );
  REQUIRE( row(Field::e8) == 8 );
  REQUIRE( row(Field::f8) == 8 );
  REQUIRE( row(Field::g8) == 8 );
  REQUIRE( row(Field::h8) == 8 );

  REQUIRE_THROWS( row(Field::none) );
}

TEST_CASE("Field: toField()")
{
  using namespace simplechess;

  REQUIRE( toField('a', 1) == Field::a1 );
  REQUIRE( toField('a', 2) == Field::a2 );
  REQUIRE( toField('a', 3) == Field::a3 );
  REQUIRE( toField('a', 4) == Field::a4 );
  REQUIRE( toField('a', 5) == Field::a5 );
  REQUIRE( toField('a', 6) == Field::a6 );
  REQUIRE( toField('a', 7) == Field::a7 );
  REQUIRE( toField('a', 8) == Field::a8 );

  REQUIRE( toField('b', 1) == Field::b1 );
  REQUIRE( toField('b', 8) == Field::b8 );
  REQUIRE( toField('c', 1) == Field::c1 );
  REQUIRE( toField('c', 8) == Field::c8 );
  REQUIRE( toField('d', 1) == Field::d1 );
  REQUIRE( toField('d', 8) == Field::d8 );
  REQUIRE( toField('e', 1) == Field::e1 );
  REQUIRE( toField('e', 8) == Field::e8 );
  REQUIRE( toField('f', 1) == Field::f1 );
  REQUIRE( toField('f', 8) == Field::f8 );
  REQUIRE( toField('g', 1) == Field::g1 );
  REQUIRE( toField('g', 8) == Field::g8 );
  REQUIRE( toField('h', 1) == Field::h1 );
  REQUIRE( toField('h', 8) == Field::h8 );
}

TEST_CASE("Field: sameFile()")
{
  using namespace simplechess;

  REQUIRE( sameFile(Field::a1, Field::a1) );
  REQUIRE( sameFile(Field::a1, Field::a2) );
  REQUIRE( sameFile(Field::a1, Field::a3) );
  REQUIRE( sameFile(Field::a1, Field::a4) );
  REQUIRE( sameFile(Field::a1, Field::a5) );
  REQUIRE( sameFile(Field::a1, Field::a6) );
  REQUIRE( sameFile(Field::a1, Field::a7) );
  REQUIRE( sameFile(Field::a1, Field::a8) );

  REQUIRE( !sameFile(Field::a1, Field::b1) );
  REQUIRE( !sameFile(Field::a1, Field::c1) );
  REQUIRE( !sameFile(Field::a1, Field::d1) );
  REQUIRE( !sameFile(Field::a1, Field::e1) );
  REQUIRE( !sameFile(Field::a1, Field::f1) );
  REQUIRE( !sameFile(Field::a1, Field::g1) );
  REQUIRE( !sameFile(Field::a1, Field::h1) );

  REQUIRE( sameFile(Field::b1, Field::b2) );
  REQUIRE( sameFile(Field::c1, Field::c3) );
  REQUIRE( sameFile(Field::d1, Field::d4) );
  REQUIRE( sameFile(Field::e1, Field::e5) );
  REQUIRE( sameFile(Field::f1, Field::f6) );
  REQUIRE( sameFile(Field::g1, Field::g7) );
  REQUIRE( sameFile(Field::h1, Field::h8) );

  REQUIRE( !sameFile(Field::a1, Field::none) );
  REQUIRE( !sameFile(Field::none, Field::a1) );
  REQUIRE( !sameFile(Field::none, Field::none) );
}

TEST_CASE("Field: sameRank()")
{
  using namespace simplechess;

  REQUIRE( sameRank(Field::a1, Field::a1) );
  REQUIRE( sameRank(Field::a1, Field::b1) );
  REQUIRE( sameRank(Field::a1, Field::c1) );
  REQUIRE( sameRank(Field::a1, Field::d1) );
  REQUIRE( sameRank(Field::a1, Field::e1) );
  REQUIRE( sameRank(Field::a1, Field::f1) );
  REQUIRE( sameRank(Field::a1, Field::g1) );
  REQUIRE( sameRank(Field::a1, Field::h1) );

  REQUIRE( !sameRank(Field::a1, Field::a2) );
  REQUIRE( !sameRank(Field::a1, Field::a3) );
  REQUIRE( !sameRank(Field::a1, Field::a4) );
  REQUIRE( !sameRank(Field::a1, Field::a5) );
  REQUIRE( !sameRank(Field::a1, Field::a6) );
  REQUIRE( !sameRank(Field::a1, Field::a7) );
  REQUIRE( !sameRank(Field::a1, Field::a8) );

  REQUIRE( sameRank(Field::b2, Field::c2) );
  REQUIRE( sameRank(Field::c3, Field::d3) );
  REQUIRE( sameRank(Field::d4, Field::e4) );
  REQUIRE( sameRank(Field::e5, Field::f5) );
  REQUIRE( sameRank(Field::f6, Field::g6) );
  REQUIRE( sameRank(Field::g7, Field::h7) );
  REQUIRE( sameRank(Field::h8, Field::a8) );

  REQUIRE( !sameRank(Field::a1, Field::none) );
  REQUIRE( !sameRank(Field::none, Field::a1) );
  REQUIRE( !sameRank(Field::none, Field::none) );
}
