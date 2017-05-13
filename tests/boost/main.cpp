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

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE forsythEdwardsNotation
#include <boost/test/unit_test.hpp>

#include "../../data/Board.hpp"
#include "../../data/ForsythEdwardsNotation.hpp"

BOOST_AUTO_TEST_CASE(defaultStartPoistion)
{
  simplechess::Board board;
  BOOST_REQUIRE(board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"));

  //There should be 32 empty fields in rows 3 to 6.
  for(int i = 3; i<=6; ++i)
  {
    for (char j = 'a'; j < 'h'; ++j)
    {
      BOOST_CHECK(simplechess::Piece(simplechess::Colour::none, simplechess::PieceType::none)
                  == board.element(simplechess::toField(j, i))
                       );
    } //for j
  } //for i
  //There should be 8 white pawns in row 2, ...
  for (char col = 'a'; col <= 'h'; ++col)
  {
    BOOST_CHECK(
        simplechess::Piece(simplechess::Colour::white, simplechess::PieceType::pawn)
        == board.element(simplechess::toField(col, 2))
    );
  } //for
  // ... and 8 black pawns in row 7.
  for (char col = 'a'; col <= 'h'; ++col)
  {
    BOOST_CHECK(
        simplechess::Piece(simplechess::Colour::black, simplechess::PieceType::pawn)
        == board.element(simplechess::toField(col, 7))
    );
  } //for
  //check white pieces
  BOOST_REQUIRE(
      simplechess::Piece(simplechess::Colour::white, simplechess::PieceType::rook)
      == board.element(simplechess::Field::a1)
  );
  BOOST_REQUIRE(
      simplechess::Piece(simplechess::Colour::white, simplechess::PieceType::knight)
      == board.element(simplechess::Field::b1)
  );
  BOOST_REQUIRE(
      simplechess::Piece(simplechess::Colour::white, simplechess::PieceType::bishop)
      == board.element(simplechess::Field::c1)
  );
  BOOST_REQUIRE(
      simplechess::Piece(simplechess::Colour::white, simplechess::PieceType::queen)
      == board.element(simplechess::Field::d1)
  );
  BOOST_REQUIRE(
      simplechess::Piece(simplechess::Colour::white, simplechess::PieceType::king)
      == board.element(simplechess::Field::e1)
  );
  BOOST_REQUIRE(
      simplechess::Piece(simplechess::Colour::white, simplechess::PieceType::bishop)
      == board.element(simplechess::Field::f1)
  );
  BOOST_REQUIRE(
      simplechess::Piece(simplechess::Colour::white, simplechess::PieceType::knight)
      == board.element(simplechess::Field::g1)
  );
  BOOST_REQUIRE(
      simplechess::Piece(simplechess::Colour::white, simplechess::PieceType::rook)
      == board.element(simplechess::Field::h1)
  );
  //check black pieces
  BOOST_REQUIRE(
      simplechess::Piece(simplechess::Colour::black, simplechess::PieceType::rook)
      == board.element(simplechess::Field::a8)
  );
  BOOST_REQUIRE(
      simplechess::Piece(simplechess::Colour::black, simplechess::PieceType::knight)
      == board.element(simplechess::Field::b8)
  );
  BOOST_REQUIRE(
      simplechess::Piece(simplechess::Colour::black, simplechess::PieceType::bishop)
      == board.element(simplechess::Field::c8)
  );
  BOOST_REQUIRE(
      simplechess::Piece(simplechess::Colour::black, simplechess::PieceType::queen)
      == board.element(simplechess::Field::d8)
  );
  BOOST_REQUIRE(
      simplechess::Piece(simplechess::Colour::black, simplechess::PieceType::king)
      == board.element(simplechess::Field::e8)
  );
  BOOST_REQUIRE(
      simplechess::Piece(simplechess::Colour::black, simplechess::PieceType::bishop)
      == board.element(simplechess::Field::f8)
  );
  BOOST_REQUIRE(
      simplechess::Piece(simplechess::Colour::black, simplechess::PieceType::knight)
      == board.element(simplechess::Field::g8)
  );
  BOOST_REQUIRE(
      simplechess::Piece(simplechess::Colour::black, simplechess::PieceType::rook)
      == board.element(simplechess::Field::h8)
  );
}

BOOST_AUTO_TEST_CASE(fromBoardToFEN)
{
  const std::string fenString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -";

  simplechess::Board board;
  BOOST_REQUIRE(board.fromFEN(fenString));

  std::string fen = simplechess::ForsythEdwardsNotation::fromBoard(board);

  BOOST_REQUIRE_EQUAL(fen, fenString);
}
