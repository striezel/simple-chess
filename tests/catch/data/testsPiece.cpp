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
#include "../../../data/Piece.hpp"

TEST_CASE("Piece default constructor")
{
  using namespace simplechess;

  Piece p;
  REQUIRE( p.colour == Colour::none );
  REQUIRE( p.piece == PieceType::none );
}

TEST_CASE("Piece constructor with parameters")
{
  using namespace simplechess;

  Piece p(Colour::white, PieceType::king);
  REQUIRE( p.colour == Colour::white );
  REQUIRE( p.piece == PieceType::king );

  p = Piece(Colour::black, PieceType::queen);
  REQUIRE( p.colour == Colour::black );
  REQUIRE( p.piece == PieceType::queen );
}

TEST_CASE("Piece::acceptable()")
{
  using namespace simplechess;

  Piece p;
  REQUIRE( p.acceptable() );

  p = Piece(Colour::white, PieceType::king);
  REQUIRE( p.acceptable() );

  p = Piece(Colour::black, PieceType::queen);
  REQUIRE( p.acceptable() );

  //negative examples
  p = Piece(Colour::black, PieceType::none);
  REQUIRE_FALSE( p.acceptable() );

  p = Piece(Colour::white, PieceType::none);
  REQUIRE_FALSE( p.acceptable() );

  p = Piece(Colour::none, PieceType::pawn);
  REQUIRE_FALSE( p.acceptable() );

  p = Piece(Colour::none, PieceType::rook);
  REQUIRE_FALSE( p.acceptable() );
}

TEST_CASE("Piece: equality operator")
{
  using namespace simplechess;

  Piece p1;
  Piece p2;
  REQUIRE( p1 == p2 );

  p1 = Piece(Colour::white, PieceType::king);
  p2 = Piece(Colour::white, PieceType::king);
  REQUIRE( p1 == p2 );

  p1 = Piece(Colour::black, PieceType::queen);
  p2 = Piece(Colour::black, PieceType::queen);
  REQUIRE( p1 == p2 );

  //negative examples
  p1 = Piece(Colour::black, PieceType::none);
  p2 = Piece(Colour::black, PieceType::knight);
  REQUIRE_FALSE( p1 == p2 );

  p1 = Piece(Colour::white, PieceType::bishop);
  p2 = Piece(Colour::black, PieceType::bishop);
  REQUIRE_FALSE( p1 == p2 );

  p1 = Piece(Colour::none, PieceType::pawn);
  p2 = Piece(Colour::white, PieceType::pawn);
  REQUIRE_FALSE( p1 == p2 );
}

TEST_CASE("Piece: inequality operator")
{
  using namespace simplechess;

  Piece p1;
  Piece p2;
  REQUIRE_FALSE( p1 != p2 );

  p1 = Piece(Colour::white, PieceType::king);
  p2 = Piece(Colour::white, PieceType::king);
  REQUIRE_FALSE( p1 != p2 );

  p1 = Piece(Colour::black, PieceType::queen);
  p2 = Piece(Colour::black, PieceType::queen);
  REQUIRE_FALSE( p1 != p2 );

  p1 = Piece(Colour::black, PieceType::none);
  p2 = Piece(Colour::black, PieceType::knight);
  REQUIRE( p1 != p2 );

  p1 = Piece(Colour::white, PieceType::bishop);
  p2 = Piece(Colour::black, PieceType::bishop);
  REQUIRE( p1 != p2 );

  p1 = Piece(Colour::none, PieceType::pawn);
  p2 = Piece(Colour::white, PieceType::pawn);
  REQUIRE( p1 != p2 );
}
