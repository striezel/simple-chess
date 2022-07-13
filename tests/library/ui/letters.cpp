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

#include "../../locate_catch.hpp"
#include "../../../libsimple-chess/ui/letters.hpp"

TEST_CASE("letters for pieces")
{
  using namespace simplechess;

  REQUIRE( ui::letter(Piece(Colour::black, PieceType::king)) == 'k' );
  REQUIRE( ui::letter(Piece(Colour::black, PieceType::queen)) == 'q' );
  REQUIRE( ui::letter(Piece(Colour::black, PieceType::bishop)) == 'b' );
  REQUIRE( ui::letter(Piece(Colour::black, PieceType::knight)) == 'n' );
  REQUIRE( ui::letter(Piece(Colour::black, PieceType::rook)) == 'r' );
  REQUIRE( ui::letter(Piece(Colour::black, PieceType::pawn)) == 'p' );

  REQUIRE( ui::letter(Piece(Colour::white, PieceType::king)) == 'K' );
  REQUIRE( ui::letter(Piece(Colour::white, PieceType::queen)) == 'Q' );
  REQUIRE( ui::letter(Piece(Colour::white, PieceType::bishop)) == 'B' );
  REQUIRE( ui::letter(Piece(Colour::white, PieceType::knight)) == 'N' );
  REQUIRE( ui::letter(Piece(Colour::white, PieceType::rook)) == 'R' );
  REQUIRE( ui::letter(Piece(Colour::white, PieceType::pawn)) == 'P' );

  REQUIRE( ui::letter(Piece(Colour::none, PieceType::none)) == ' ' );
  REQUIRE( ui::letter(Piece(Colour::black, PieceType::none)) == ' ' );
  REQUIRE( ui::letter(Piece(Colour::white, PieceType::none)) == ' ' );
}
