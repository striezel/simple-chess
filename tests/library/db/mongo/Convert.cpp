/*
 -------------------------------------------------------------------------------
    This file is part of the test suite for simple-chess.
    Copyright (C) 2023  Dirk Stolle

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

#include "../../../locate_catch.hpp"
#include "../../../../libsimple-chess/db/mongo/Convert.hpp"

TEST_CASE("db::mongo::Convert")
{
  using namespace simplechess;
  using namespace simplechess::db::mongo;

  SECTION("toPiece")
  {
    SECTION("white pieces")
    {
      auto p = Convert::toPiece("pawn", "white");
      REQUIRE( p == Piece(Colour::white, PieceType::pawn) );

      p = Convert::toPiece("rook", "white");
      REQUIRE( p == Piece(Colour::white, PieceType::rook) );

      p = Convert::toPiece("knight", "white");
      REQUIRE( p == Piece(Colour::white, PieceType::knight) );

      p = Convert::toPiece("bishop", "white");
      REQUIRE( p == Piece(Colour::white, PieceType::bishop) );

      p = Convert::toPiece("queen", "white");
      REQUIRE( p == Piece(Colour::white, PieceType::queen) );

      p = Convert::toPiece("king", "white");
      REQUIRE( p == Piece(Colour::white, PieceType::king) );
    }

    SECTION("black pieces")
    {
      auto p = Convert::toPiece("pawn", "black");
      REQUIRE( p == Piece(Colour::black, PieceType::pawn) );

      p = Convert::toPiece("rook", "black");
      REQUIRE( p == Piece(Colour::black, PieceType::rook) );

      p = Convert::toPiece("knight", "black");
      REQUIRE( p == Piece(Colour::black, PieceType::knight) );

      p = Convert::toPiece("bishop", "black");
      REQUIRE( p == Piece(Colour::black, PieceType::bishop) );

      p = Convert::toPiece("queen", "black");
      REQUIRE( p == Piece(Colour::black, PieceType::queen) );

      p = Convert::toPiece("king", "black");
      REQUIRE( p == Piece(Colour::black, PieceType::king) );
    }

    SECTION("empty piece")
    {
      const auto p = Convert::toPiece("empty", "empty");
      REQUIRE( p == Piece(Colour::none, PieceType::none) );
    }

    SECTION("invalid piece")
    {
      auto p = Convert::toPiece("foo", "bar");
      REQUIRE_FALSE( p.acceptable() );

      p = Convert::toPiece("foo", "white");
      REQUIRE_FALSE( p.acceptable() );

      p = Convert::toPiece("pawn", "foo");
      REQUIRE_FALSE( p.acceptable() );
    }
  }

  SECTION("toField")
  {
    SECTION("acceptable values")
    {
      REQUIRE( Convert::toField("a", 1) == Field::a1 );
      REQUIRE( Convert::toField("a", 2) == Field::a2 );
      REQUIRE( Convert::toField("a", 3) == Field::a3 );
      REQUIRE( Convert::toField("a", 4) == Field::a4 );
      REQUIRE( Convert::toField("a", 5) == Field::a5 );
      REQUIRE( Convert::toField("a", 6) == Field::a6 );
      REQUIRE( Convert::toField("a", 7) == Field::a7 );
      REQUIRE( Convert::toField("a", 8) == Field::a8 );

      REQUIRE( Convert::toField("b", 1) == Field::b1 );
      REQUIRE( Convert::toField("c", 1) == Field::c1 );
      REQUIRE( Convert::toField("d", 1) == Field::d1 );
      REQUIRE( Convert::toField("e", 1) == Field::e1 );
      REQUIRE( Convert::toField("f", 1) == Field::f1 );
      REQUIRE( Convert::toField("g", 1) == Field::g1 );
      REQUIRE( Convert::toField("h", 1) == Field::h1 );
      REQUIRE( Convert::toField("h", 8) == Field::h8 );
    }

    SECTION("invalid input")
    {
      REQUIRE( Convert::toField("", 1) == Field::none );
      REQUIRE( Convert::toField("a", 0) == Field::none );
      REQUIRE( Convert::toField("a", 9) == Field::none );
      REQUIRE( Convert::toField("_", 1) == Field::none );
      REQUIRE( Convert::toField("i", 2) == Field::none );
    }
  }

  SECTION("colourToMongoDbString")
  {
    REQUIRE( Convert::colourToMongoDbString(Colour::none) == "empty" );
    REQUIRE( Convert::colourToMongoDbString(Colour::black) == "black" );
    REQUIRE( Convert::colourToMongoDbString(Colour::white) == "white" );

    const Colour invalid = static_cast<Colour>(static_cast<int>(Colour::none) + 5);
    REQUIRE_THROWS( Convert::colourToMongoDbString(invalid) );
  }

  SECTION("pieceToString")
  {
    REQUIRE( Convert::pieceToString(PieceType::none) == "empty" );
    REQUIRE( Convert::pieceToString(PieceType::pawn) == "pawn" );
    REQUIRE( Convert::pieceToString(PieceType::rook) == "rook" );
    REQUIRE( Convert::pieceToString(PieceType::knight) == "knight" );
    REQUIRE( Convert::pieceToString(PieceType::bishop) == "bishop" );
    REQUIRE( Convert::pieceToString(PieceType::queen) == "queen" );
    REQUIRE( Convert::pieceToString(PieceType::king) == "king" );

    const PieceType invalid = static_cast<PieceType>(static_cast<int>(PieceType::none) + 15);
    REQUIRE_THROWS( Convert::pieceToString(invalid) );
  }
}
