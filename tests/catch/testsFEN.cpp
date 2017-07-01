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

#include "../../data/Board.hpp"

TEST_CASE("defaultStartPosition")
{
  using namespace simplechess;
  Board board;
  REQUIRE(board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"));

  //There should be 32 empty fields in rows 3 to 6.
  for(int i = 3; i<=6; ++i)
  {
    for (char j = 'a'; j < 'h'; ++j)
    {
      CHECK(Piece(Colour::none, PieceType::none) == board.element(toField(j, i)));
    } //for j
  } //for i
  //There should be 8 white pawns in row 2, ...
  for (char col = 'a'; col <= 'h'; ++col)
  {
    CHECK(Piece(Colour::white, PieceType::pawn) == board.element(toField(col, 2))
    );
  } //for
  // ... and 8 black pawns in row 7.
  for (char col = 'a'; col <= 'h'; ++col)
  {
    CHECK(
        Piece(Colour::black, PieceType::pawn) == board.element(toField(col, 7))
    );
  } //for
  //check white pieces
  REQUIRE(
      Piece(Colour::white, PieceType::rook) == board.element(Field::a1)
  );
  REQUIRE(
      Piece(Colour::white, PieceType::knight) == board.element(Field::b1)
  );
  REQUIRE(
      Piece(Colour::white, PieceType::bishop) == board.element(Field::c1)
  );
  REQUIRE(
      Piece(Colour::white, PieceType::queen) == board.element(Field::d1)
  );
  REQUIRE(
      Piece(Colour::white, PieceType::king) == board.element(Field::e1)
  );
  REQUIRE(
      Piece(Colour::white, PieceType::bishop) == board.element(Field::f1)
  );
  REQUIRE(
      Piece(Colour::white, PieceType::knight) == board.element(Field::g1)
  );
  REQUIRE(
      Piece(Colour::white, PieceType::rook) == board.element(Field::h1)
  );
  //check black pieces
  REQUIRE(
      Piece(Colour::black, PieceType::rook) == board.element(Field::a8)
  );
  REQUIRE(
      Piece(Colour::black, PieceType::knight) == board.element(Field::b8)
  );
  REQUIRE(
      Piece(Colour::black, PieceType::bishop) == board.element(Field::c8)
  );
  REQUIRE(
      Piece(Colour::black, PieceType::queen) == board.element(Field::d8)
  );
  REQUIRE(
      Piece(Colour::black, PieceType::king) == board.element(Field::e8)
  );
  REQUIRE(
      Piece(Colour::black, PieceType::bishop) == board.element(Field::f8)
  );
  REQUIRE(
      Piece(Colour::black, PieceType::knight) == board.element(Field::g8)
  );
  REQUIRE(
      Piece(Colour::black, PieceType::rook) == board.element(Field::h8)
  );
}
