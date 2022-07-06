/*
 -------------------------------------------------------------------------------
    This file is part of the test suite for simple-chess.
    Copyright (C) 2022  Dirk Stolle

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

#include "../locate_catch.hpp"
#include "../../../libsimple-chess/ui/symbols.hpp"

TEST_CASE("Unicode symbols for pieces")
{
  using namespace std::string_view_literals;
  using namespace simplechess;

  REQUIRE( ui::symbol(Piece(Colour::black, PieceType::king)) == "\xe2\x99\x9a"sv );
  REQUIRE( ui::symbol(Piece(Colour::black, PieceType::queen)) == "\xe2\x99\x9b"sv );
  REQUIRE( ui::symbol(Piece(Colour::black, PieceType::bishop)) == "\xe2\x99\x9d"sv );
  REQUIRE( ui::symbol(Piece(Colour::black, PieceType::knight)) == "\xe2\x99\x9e"sv );
  REQUIRE( ui::symbol(Piece(Colour::black, PieceType::rook)) == "\xe2\x99\x9c"sv );
  REQUIRE( ui::symbol(Piece(Colour::black, PieceType::pawn)) == "\xe2\x99\x9f"sv );

  REQUIRE( ui::symbol(Piece(Colour::white, PieceType::king)) == "\xe2\x99\x94"sv );
  REQUIRE( ui::symbol(Piece(Colour::white, PieceType::queen)) == "\xe2\x99\x95"sv );
  REQUIRE( ui::symbol(Piece(Colour::white, PieceType::bishop)) == "\xe2\x99\x97"sv );
  REQUIRE( ui::symbol(Piece(Colour::white, PieceType::knight)) == "\xe2\x99\x98"sv );
  REQUIRE( ui::symbol(Piece(Colour::white, PieceType::rook)) == "\xe2\x99\x96"sv );
  REQUIRE( ui::symbol(Piece(Colour::white, PieceType::pawn)) == "\xe2\x99\x99"sv );

  REQUIRE( ui::symbol(Piece(Colour::none, PieceType::none)) == " " );
  REQUIRE( ui::symbol(Piece(Colour::black, PieceType::none)) == " " );
  REQUIRE( ui::symbol(Piece(Colour::white, PieceType::none)) == " " );
}
