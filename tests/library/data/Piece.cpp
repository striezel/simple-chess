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
#include <sstream>
#include "../../../libsimple-chess/data/Piece.hpp"

TEST_CASE("Piece default constructor")
{
  using namespace simplechess;

  Piece p;
  REQUIRE( p.colour() == Colour::none );
  REQUIRE( p.piece() == PieceType::none );
}

TEST_CASE("Piece constructor with parameters")
{
  using namespace simplechess;

  Piece p(Colour::white, PieceType::king);
  REQUIRE( p.colour() == Colour::white );
  REQUIRE( p.piece() == PieceType::king );

  p = Piece(Colour::black, PieceType::queen);
  REQUIRE( p.colour() == Colour::black );
  REQUIRE( p.piece() == PieceType::queen );
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

  // negative examples
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

  // negative examples
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

TEST_CASE("stream operator: Colour")
{
  using namespace simplechess;

  std::ostringstream stream;

  SECTION("black")
  {
    stream << Colour::black;
    REQUIRE( stream.str() == "black" );
  }

  SECTION("white")
  {
    stream << Colour::white;
    REQUIRE( stream.str() == "white" );
  }

  SECTION("none")
  {
    stream << Colour::none;
    REQUIRE( stream.str() == "none" );
  }
}

TEST_CASE("stream operator: PieceType")
{
  using namespace simplechess;

  std::ostringstream stream;

  SECTION("king")
  {
    stream << PieceType::king;
    REQUIRE( stream.str() == "king" );
  }

  SECTION("queen")
  {
    stream << PieceType::queen;
    REQUIRE( stream.str() == "queen" );
  }

  SECTION("bishop")
  {
    stream << PieceType::bishop;
    REQUIRE( stream.str() == "bishop" );
  }

  SECTION("knight")
  {
    stream << PieceType::knight;
    REQUIRE( stream.str() == "knight" );
  }

  SECTION("rook")
  {
    stream << PieceType::rook;
    REQUIRE( stream.str() == "rook" );
  }

  SECTION("pawn")
  {
    stream << PieceType::pawn;
    REQUIRE( stream.str() == "pawn" );
  }

  SECTION("none")
  {
    stream << PieceType::none;
    REQUIRE( stream.str() == "none" );
  }
}

TEST_CASE("stream operator: Piece")
{
  using namespace simplechess;

  std::ostringstream stream;

  SECTION("w")
  {
    SECTION("king")
    {
      stream << Piece(Colour::white, PieceType::king);
      REQUIRE( stream.str() == "Piece(white king)" );
    }

    SECTION("queen")
    {
      stream << Piece(Colour::white, PieceType::queen);
      REQUIRE( stream.str() == "Piece(white queen)" );
    }

    SECTION("bishop")
    {
      stream << Piece(Colour::white, PieceType::bishop);
      REQUIRE( stream.str() == "Piece(white bishop)" );
    }

    SECTION("knight")
    {
      stream << Piece(Colour::white, PieceType::knight);
      REQUIRE( stream.str() == "Piece(white knight)" );
    }

    SECTION("rook")
    {
      stream << Piece(Colour::white, PieceType::rook);
      REQUIRE( stream.str() == "Piece(white rook)" );
    }

    SECTION("pawn")
    {
      stream << Piece(Colour::white, PieceType::pawn);
      REQUIRE( stream.str() == "Piece(white pawn)" );
    }

    SECTION("none")
    {
      stream << Piece(Colour::white, PieceType::none);
      REQUIRE( stream.str() == "Piece(white none)" );
    }
  }

  SECTION("none")
  {
    // Does not really happen, but let's cover this case anyway.
    stream << Piece(Colour::none, PieceType::none);
    REQUIRE( stream.str() == "Piece(none none)" );
  }

  SECTION("b")
  {
    SECTION("king")
    {
      stream << Piece(Colour::black, PieceType::king);
      REQUIRE( stream.str() == "Piece(black king)" );
    }

    SECTION("queen")
    {
      stream << Piece(Colour::black, PieceType::queen);
      REQUIRE( stream.str() == "Piece(black queen)" );
    }

    SECTION("bishop")
    {
      stream << Piece(Colour::black, PieceType::bishop);
      REQUIRE( stream.str() == "Piece(black bishop)" );
    }

    SECTION("knight")
    {
      stream << Piece(Colour::black, PieceType::knight);
      REQUIRE( stream.str() == "Piece(black knight)" );
    }

    SECTION("rook")
    {
      stream << Piece(Colour::black, PieceType::rook);
      REQUIRE( stream.str() == "Piece(black rook)" );
    }

    SECTION("pawn")
    {
      stream << Piece(Colour::black, PieceType::pawn);
      REQUIRE( stream.str() == "Piece(black pawn)" );
    }

    SECTION("none")
    {
      stream << Piece(Colour::black, PieceType::none);
      REQUIRE( stream.str() == "Piece(black none)" );
    }
  }
}
