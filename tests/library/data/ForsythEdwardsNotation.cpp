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


#include "../locate_catch.hpp"

#include "../../../libsimple-chess/data/Board.hpp"
#include "../../../libsimple-chess/data/ForsythEdwardsNotation.hpp"

TEST_CASE("ForsythEdwardsNotation::fromBoard()")
{
  using namespace simplechess;
  Board board;

  SECTION("default initial position")
  {
    REQUIRE(board.fromFEN(FEN::defaultInitialPosition));
    const std::string fen = ForsythEdwardsNotation::fromBoard(board);
    REQUIRE(fen == FEN::defaultInitialPosition);
  }

  SECTION("non-standard position")
  {
    // white pieces
    board.setElement(Field::a2, Piece(Colour::white, PieceType::pawn));
    board.setElement(Field::b2, Piece(Colour::white, PieceType::pawn));
    board.setElement(Field::c2, Piece(Colour::white, PieceType::pawn));
    board.setElement(Field::d3, Piece(Colour::white, PieceType::pawn));
    board.setElement(Field::g2, Piece(Colour::white, PieceType::pawn));
    board.setElement(Field::h1, Piece(Colour::white, PieceType::king));
    board.setElement(Field::g8, Piece(Colour::white, PieceType::rook));
    board.setElement(Field::h7, Piece(Colour::white, PieceType::queen));
    // black pieces
    board.setElement(Field::a7, Piece(Colour::black, PieceType::pawn));
    board.setElement(Field::b6, Piece(Colour::black, PieceType::pawn));
    board.setElement(Field::c7, Piece(Colour::black, PieceType::pawn));
    board.setElement(Field::d7, Piece(Colour::black, PieceType::pawn));
    board.setElement(Field::f4, Piece(Colour::black, PieceType::pawn));
    board.setElement(Field::a8, Piece(Colour::black, PieceType::rook));
    board.setElement(Field::c8, Piece(Colour::black, PieceType::bishop));
    board.setElement(Field::f7, Piece(Colour::black, PieceType::king));
    board.setElement(Field::g6, Piece(Colour::black, PieceType::knight));
    // update who is to move
    board.setToMove(Colour::black);
    // update castling info
    Castling c;
    c.fromFEN("-");
    board.setCastling(c);
    // update number of half moves for 50 move rule
    board.setHalfmovesFifty(34);

    const std::string expectedFEN = "r1b3R1/p1pp1k1Q/1p4n1/8/5p2/3P4/PPP3P1/7K b - - 34";
    const std::string actualFEN = ForsythEdwardsNotation::fromBoard(board);
    REQUIRE(expectedFEN == actualFEN);
  }
}
