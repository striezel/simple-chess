/*
 -------------------------------------------------------------------------------
    This file is part of the test suite for simple-chess.
    Copyright (C) 2017, 2018, 2023  Dirk Stolle

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
#include "../../../libsimple-chess/data/Board.hpp"
#include "../../../libsimple-chess/data/ForsythEdwardsNotation.hpp"

TEST_CASE("Board constructor")
{
  using namespace simplechess;

  SECTION("constructor")
  {
    Board board;

    const Piece empty { Colour::none, PieceType::none };
    for (int i = static_cast<int>(Field::a1); i <= static_cast<int>(Field::h8); ++i)
    {
      REQUIRE( board.element(static_cast<Field>(i)) == empty );
    }
  }

  SECTION("Board::element()")
  {
    Board board;
    REQUIRE( board.setElement(Field::e1, Piece(Colour::white, PieceType::king)) );

    SECTION("valid field")
    {
      REQUIRE( board.element(Field::e1) == Piece(Colour::white, PieceType::king) );
      REQUIRE( board.element(Field::e4) == Piece() );
    }

    SECTION("invalid field")
    {
      REQUIRE_THROWS( board.element(Field::none) );
    }
  }

  SECTION("Board::setElement()")
  {
    Board board;

    SECTION("valid field")
    {
      REQUIRE( board.setElement(Field::e8, Piece(Colour::black, PieceType::king)) );
      REQUIRE( board.element(Field::e8) == Piece(Colour::black, PieceType::king) );

      REQUIRE( board.setElement(Field::d8, Piece(Colour::black, PieceType::queen)) );
      REQUIRE( board.element(Field::d8) == Piece(Colour::black, PieceType::queen) );
    }

    SECTION("invalid field")
    {
      REQUIRE_FALSE( board.setElement(Field::none, Piece()) );
    }
  }

  SECTION("Board::setToMove() + Board::toMove()")
  {
    Board board;

    REQUIRE( board.setToMove(Colour::white) );
    REQUIRE( board.toMove() == Colour::white );

    REQUIRE( board.setToMove(Colour::black) );
    REQUIRE( board.toMove() == Colour::black );

    REQUIRE_FALSE( board.setToMove(Colour::none) );
    REQUIRE( board.toMove() == Colour::black );
  }

  SECTION("Board::setEnPassant()")
  {
    Board board;

    REQUIRE( board.setEnPassant(Field::none) );
    REQUIRE( board.enPassant() == Field::none );

    REQUIRE( board.setEnPassant(Field::a3) );
    REQUIRE( board.enPassant() == Field::a3 );
    REQUIRE( board.setEnPassant(Field::b3) );
    REQUIRE( board.enPassant() == Field::b3 );
    REQUIRE( board.setEnPassant(Field::c3) );
    REQUIRE( board.setEnPassant(Field::d3) );
    REQUIRE( board.setEnPassant(Field::e3) );
    REQUIRE( board.setEnPassant(Field::f3) );
    REQUIRE( board.setEnPassant(Field::g3) );
    REQUIRE( board.setEnPassant(Field::h3) );
    REQUIRE( board.enPassant() == Field::h3 );

    REQUIRE( board.setEnPassant(Field::a6) );
    REQUIRE( board.enPassant() == Field::a6 );
    REQUIRE( board.setEnPassant(Field::b6) );
    REQUIRE( board.setEnPassant(Field::c6) );
    REQUIRE( board.setEnPassant(Field::d6) );
    REQUIRE( board.setEnPassant(Field::e6) );
    REQUIRE( board.enPassant() == Field::e6 );
    REQUIRE( board.setEnPassant(Field::f6) );
    REQUIRE( board.setEnPassant(Field::g6) );
    REQUIRE( board.setEnPassant(Field::h6) );
    REQUIRE( board.enPassant() == Field::h6 );

    REQUIRE_FALSE( board.setEnPassant(Field::a1) );
    REQUIRE_FALSE( board.setEnPassant(Field::a2) );
    REQUIRE_FALSE( board.setEnPassant(Field::a4) );
    REQUIRE_FALSE( board.setEnPassant(Field::a5) );
    REQUIRE_FALSE( board.setEnPassant(Field::a7) );
    REQUIRE_FALSE( board.setEnPassant(Field::a7) );
  }

  SECTION("Board::isInCheck()")
  {
    Board board;

    SECTION("white is in check")
    {
      REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPqPPP/RNBQKBNR w") );

      REQUIRE( board.isInCheck(Colour::white) );
      REQUIRE_FALSE( board.isInCheck(Colour::black) );
      REQUIRE_FALSE( board.isInCheck(Colour::none) );
    }

    SECTION("black is in check")
    {
      REQUIRE( board.fromFEN("rnbqkbnr/ppppQppp/8/8/8/8/PPPPPPPP/RNBQKBNR b") );

      REQUIRE_FALSE( board.isInCheck(Colour::white) );
      REQUIRE( board.isInCheck(Colour::black) );
      REQUIRE_FALSE( board.isInCheck(Colour::none) );
    }

    SECTION("nobody in check")
    {
      REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR") );

      REQUIRE_FALSE( board.isInCheck(Colour::white) );
      REQUIRE_FALSE( board.isInCheck(Colour::black) );
      REQUIRE_FALSE( board.isInCheck(Colour::none) );
    }
  }
}

TEST_CASE("Board::fromFEN() with default start position")
{
  using namespace simplechess;
  Board board;
  REQUIRE(board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"));

  // There should be 32 empty fields in rows 3 to 6.
  for(int i = 3; i <= 6; ++i)
  {
    for (char j = 'a'; j < 'h'; ++j)
    {
      CHECK(Piece(Colour::none, PieceType::none) == board.element(toField(j, i)));
    }
  }
  // There should be 8 white pawns in row 2, ...
  for (char col = 'a'; col <= 'h'; ++col)
  {
    CHECK(Piece(Colour::white, PieceType::pawn) == board.element(toField(col, 2))
    );
  }
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
  // White shall be the player to move next.
  REQUIRE( board.toMove() == Colour::white );
  // Check castling info: everything is possible.
  const Castling& c = board.castling();
  REQUIRE( c.black_kingside );
  REQUIRE( c.black_queenside );
  REQUIRE( c.black_castled == Ternary::false_value );
  REQUIRE( c.white_kingside );
  REQUIRE( c.white_queenside );
  REQUIRE( c.white_castled == Ternary::false_value );
  // No en passant field.
  REQUIRE( board.enPassant() == Field::none );
  // Fifty move rule: zero moves.
  REQUIRE( board.halfmovesFifty() == 0 );
}

TEST_CASE("Board::fromFEN() with custom position")
{
  using namespace simplechess;
  Board board;
  REQUIRE(board.fromFEN("r1b3R1/p1pp1k1Q/1p4n1/8/5p2/3P4/PPP3P1/7K b - -"));

  //check white pieces
  REQUIRE( board.element(Field::a2) == Piece(Colour::white, PieceType::pawn) );
  REQUIRE( board.element(Field::b2) == Piece(Colour::white, PieceType::pawn) );
  REQUIRE( board.element(Field::c2) == Piece(Colour::white, PieceType::pawn) );
  REQUIRE( board.element(Field::d3) == Piece(Colour::white, PieceType::pawn) );
  REQUIRE( board.element(Field::g2) == Piece(Colour::white, PieceType::pawn) );
  REQUIRE( board.element(Field::h1) == Piece(Colour::white, PieceType::king) );
  REQUIRE( board.element(Field::g8) == Piece(Colour::white, PieceType::rook) );
  REQUIRE( board.element(Field::h7) == Piece(Colour::white, PieceType::queen) );
  //check black pieces
  REQUIRE( board.element(Field::a7) == Piece(Colour::black, PieceType::pawn) );
  REQUIRE( board.element(Field::b6) == Piece(Colour::black, PieceType::pawn) );
  REQUIRE( board.element(Field::c7) == Piece(Colour::black, PieceType::pawn) );
  REQUIRE( board.element(Field::d7) == Piece(Colour::black, PieceType::pawn) );
  REQUIRE( board.element(Field::f4) == Piece(Colour::black, PieceType::pawn) );
  REQUIRE( board.element(Field::a8) == Piece(Colour::black, PieceType::rook) );
  REQUIRE( board.element(Field::c8) == Piece(Colour::black, PieceType::bishop) );
  REQUIRE( board.element(Field::f7) == Piece(Colour::black, PieceType::king) );
  REQUIRE( board.element(Field::g6) == Piece(Colour::black, PieceType::knight) );
  //count number of empty fields (easier than checking each field individually)
  int emptyFields = 0;
  Field currentField = Field::a1;
  const Piece noPiece = Piece();
  do
  {
    currentField = board.findNext(noPiece, currentField);
    if (currentField != Field::none)
    {
      ++emptyFields;
      if (currentField != Field::h8)
        currentField = static_cast<Field>(static_cast<int>(currentField) + 1);
    }
  } while ((currentField != Field::none) && (currentField != Field::h8));
  REQUIRE( emptyFields == 47 );
  // check who is to move
  REQUIRE( board.toMove() == Colour::black );
  // check e.p. info
  REQUIRE( board.enPassant() == Field::none );
  // check castling info
  const Castling& c = board.castling();
  REQUIRE_FALSE( c.black_kingside );
  REQUIRE_FALSE( c.black_queenside );
  REQUIRE( c.black_castled == Ternary::maybe_value );
  REQUIRE_FALSE( c.white_kingside );
  REQUIRE_FALSE( c.white_queenside );
  REQUIRE( c.white_castled == Ternary::maybe_value );
  // Fifty move rule: zero moves.
  REQUIRE( board.halfmovesFifty() == 0 );
}

TEST_CASE("Board::fromFEN() with en passant fields")
{
  using namespace simplechess;
  Board board;
  // none
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - -") );
  REQUIRE( board.enPassant() == Field::none );
  // a3
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - a3") );
  REQUIRE( board.enPassant() == Field::a3 );
  // b3
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - b3") );
  REQUIRE( board.enPassant() == Field::b3 );
  // c3
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - c3") );
  REQUIRE( board.enPassant() == Field::c3 );
  // d3
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - d3") );
  REQUIRE( board.enPassant() == Field::d3 );
  // e3
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - e3") );
  REQUIRE( board.enPassant() == Field::e3 );
  // f3
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - f3") );
  REQUIRE( board.enPassant() == Field::f3 );
  // g3
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - g3") );
  REQUIRE( board.enPassant() == Field::g3 );
  // h3
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - h3") );
  REQUIRE( board.enPassant() == Field::h3 );

  // a6
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - a6") );
  REQUIRE( board.enPassant() == Field::a6 );
  // b6
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - b6") );
  REQUIRE( board.enPassant() == Field::b6 );
  // c6
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - c6") );
  REQUIRE( board.enPassant() == Field::c6 );
  // d6
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - d6") );
  REQUIRE( board.enPassant() == Field::d6 );
  // e6
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - e6") );
  REQUIRE( board.enPassant() == Field::e6 );
  // f6
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - f6") );
  REQUIRE( board.enPassant() == Field::f6 );
  // g6
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - g6") );
  REQUIRE( board.enPassant() == Field::g6 );
  // h6
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - h6") );
  REQUIRE( board.enPassant() == Field::h6 );

  // no valid FEN, because e. p. field has wrong rank
  REQUIRE_FALSE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - a1") );
  REQUIRE_FALSE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - a2") );
  REQUIRE_FALSE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - a4") );
  REQUIRE_FALSE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - a5") );
  REQUIRE_FALSE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - a7") );
  REQUIRE_FALSE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - a9") );
}

TEST_CASE("Board::findNext()")
{
  using namespace simplechess;
  Board board;
  REQUIRE(board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"));

  // find piece that is only there once
  Field f = board.findNext(Piece(Colour::white, PieceType::king), Field::a1);
  REQUIRE( f == Field::e1 );
  f = board.findNext(Piece(Colour::white, PieceType::king), Field::e2);
  REQUIRE( f == Field::none );

  // find piece that exists multiple times
  f = board.findNext(Piece(Colour::black, PieceType::knight), Field::a1);
  REQUIRE( f == Field::b8 );
  f = board.findNext(Piece(Colour::black, PieceType::knight), Field::c1);
  REQUIRE( f == Field::g8 );
  f = board.findNext(Piece(Colour::black, PieceType::knight), Field::h1);
  REQUIRE( f == Field::none );
}

TEST_CASE("Board::move()")
{
  using namespace simplechess;
  Board board;

  SECTION("simple pawn move")
  {
    REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR") );
    // Set halfmoves for 50 move rule to any number larger than zero.
    board.setHalfmovesFifty(12);
    // move shall be performable
    REQUIRE( board.move(Field::e2, Field::e4, PieceType::queen) );
    // e2 shall be empty
    REQUIRE( board.element(Field::e2) == Piece() );
    // e4 shall be white pawn
    REQUIRE( board.element(Field::e4) == Piece(Colour::white, PieceType::pawn) );
    // Halfmoves under 50 move rule shall be reset to zero, because pawn moved.
    REQUIRE( board.halfmovesFifty() == 0 );
  }

  SECTION("white pawn promotion")
  {
    REQUIRE( board.fromFEN("8/P7/8/8/8/8/8/8") );

    SECTION("promote to queen")
    {
      // Set halfmoves for 50 move rule to any number larger than zero.
      board.setHalfmovesFifty(12);
      // move shall be performable
      REQUIRE( board.move(Field::a7, Field::a8, PieceType::queen) );
      // a7 shall be empty
      REQUIRE( board.element(Field::a7) == Piece() );
      // a8 shall be white queen
      REQUIRE( board.element(Field::a8) == Piece(Colour::white, PieceType::queen) );
      // Halfmoves under 50 move rule shall be reset to zero, because pawn moved.
      REQUIRE( board.halfmovesFifty() == 0 );
    }

    SECTION("promote to knight")
    {
      // Set halfmoves for 50 move rule to any number larger than zero.
      board.setHalfmovesFifty(12);
      // move shall be performable
      REQUIRE( board.move(Field::a7, Field::a8, PieceType::knight) );
      // a7 shall be empty
      REQUIRE( board.element(Field::a7) == Piece() );
      // a8 shall be white knight
      REQUIRE( board.element(Field::a8) == Piece(Colour::white, PieceType::knight) );
      // Halfmoves under 50 move rule shall be reset to zero, because pawn moved.
      REQUIRE( board.halfmovesFifty() == 0 );
    }
  }

  SECTION("en passant capture of white pawn")
  {
    REQUIRE( board.fromFEN("k6K/8/8/8/4Pp2/8/8/8 b - e3") );

    // Set halfmoves for 50 move rule to any number larger than zero.
    board.setHalfmovesFifty(12);
    // e4 shall be white pawn
    REQUIRE( board.element(Field::e4) == Piece(Colour::white, PieceType::pawn) );
    // move black pawn from f4 to e3 - should be performed
    REQUIRE( board.move(Field::f4, Field::e3, PieceType::queen) );
    // e4 should not contain white pawn anymore
    REQUIRE( board.element(Field::e4) == Piece(Colour::none, PieceType::none) );
    // Halfmoves under 50 move rule shall be reset to zero, because pawn moved.
    REQUIRE( board.halfmovesFifty() == 0 );
  }

  SECTION("black pawn promotion")
  {
    REQUIRE( board.fromFEN("8/8/8/8/8/8/p7/8 b") );

    SECTION("promote to queen")
    {
      // move shall be performable
      REQUIRE( board.move(Field::a2, Field::a1, PieceType::queen) );
      // a2 shall be empty
      REQUIRE( board.element(Field::a2) == Piece() );
      // a1 shall be black queen
      REQUIRE( board.element(Field::a1) == Piece(Colour::black, PieceType::queen) );
      // Halfmoves under 50 move rule shall be reset to zero, because pawn moved.
      REQUIRE( board.halfmovesFifty() == 0 );
    }

    SECTION("promote to knight")
    {
      // move shall be performable
      REQUIRE( board.move(Field::a2, Field::a1, PieceType::knight) );
      // a2 shall be empty
      REQUIRE( board.element(Field::a2) == Piece() );
      // a1 shall be black knight
      REQUIRE( board.element(Field::a1) == Piece(Colour::black, PieceType::knight) );
      // Halfmoves under 50 move rule shall be reset to zero, because pawn moved.
      REQUIRE( board.halfmovesFifty() == 0 );
    }
  }

  SECTION("en passant capture of black pawn")
  {
    REQUIRE( board.fromFEN("k6K/8/8/4pP2/8/8/8/8 w - e6") );
    // e5 shall be black pawn
    REQUIRE( board.element(Field::e5) == Piece(Colour::black, PieceType::pawn) );
    // move black pawn from f5 to e6 - should be performed
    REQUIRE( board.move(Field::f5, Field::e6, PieceType::queen) );
    // e5 should not contain black pawn anymore
    REQUIRE( board.element(Field::e5) == Piece(Colour::none, PieceType::none) );
    // Halfmoves under 50 move rule shall be reset to zero, because pawn was captured.
    REQUIRE( board.halfmovesFifty() == 0 );
  }

  SECTION("white kingside castling")
  {
    REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQK2R") );
    // Castling must be allowed.
    REQUIRE( board.castling().white_kingside );
    REQUIRE( board.castling().white_queenside );
    // move shall be performable
    REQUIRE( board.move(Field::e1, Field::g1, PieceType::queen) );
    // e1 shall be empty
    REQUIRE( board.element(Field::e1) == Piece() );
    // g1 shall be white king
    REQUIRE( board.element(Field::g1) == Piece(Colour::white, PieceType::king) );
    // h1 shall be empty
    REQUIRE( board.element(Field::h1) == Piece() );
    // f1 shall be white rook
    REQUIRE( board.element(Field::f1) == Piece(Colour::white, PieceType::rook) );
    // Castling for white player is not allowed anymore.
    REQUIRE_FALSE( board.castling().white_kingside );
    REQUIRE_FALSE( board.castling().white_queenside );
    // White player has castled.
    REQUIRE( board.castling().white_castled == Ternary::true_value );
  }

  SECTION("white queenside castling")
  {
    REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/R3KBNR") );
    // Castling must be allowed.
    REQUIRE( board.castling().white_kingside );
    REQUIRE( board.castling().white_queenside );
    // move shall be performable
    REQUIRE( board.move(Field::e1, Field::c1, PieceType::queen) );
    // e1 shall be empty
    REQUIRE( board.element(Field::e1) == Piece() );
    // c1 shall be white king
    REQUIRE( board.element(Field::c1) == Piece(Colour::white, PieceType::king) );
    // a1 shall be empty
    REQUIRE( board.element(Field::a1) == Piece() );
    // d1 shall be white rook
    REQUIRE( board.element(Field::d1) == Piece(Colour::white, PieceType::rook) );
    // Castling for white player is not allowed anymore.
    REQUIRE_FALSE( board.castling().white_kingside );
    REQUIRE_FALSE( board.castling().white_queenside );
    // White player has castled.
    REQUIRE( board.castling().white_castled == Ternary::true_value );
  }

  SECTION("black kingside castling")
  {
    REQUIRE( board.fromFEN("rnbqk2r/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b") );
    // Castling must be allowed.
    REQUIRE( board.castling().black_kingside );
    REQUIRE( board.castling().black_queenside );
    // move shall be performable
    REQUIRE( board.move(Field::e8, Field::g8, PieceType::queen) );
    // e8 shall be empty
    REQUIRE( board.element(Field::e8) == Piece() );
    // g8 shall be white king
    REQUIRE( board.element(Field::g8) == Piece(Colour::black, PieceType::king) );
    // h8 shall be empty
    REQUIRE( board.element(Field::h8) == Piece() );
    // f8 shall be white rook
    REQUIRE( board.element(Field::f8) == Piece(Colour::black, PieceType::rook) );
    // Castling for black player is not allowed anymore.
    REQUIRE_FALSE( board.castling().black_kingside );
    REQUIRE_FALSE( board.castling().black_queenside );
    // Black player has castled.
    REQUIRE( board.castling().black_castled == Ternary::true_value );
  }

  SECTION("black queenside castling")
  {
    REQUIRE( board.fromFEN("r3kbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b") );
    // Castling must be allowed.
    REQUIRE( board.castling().black_kingside );
    REQUIRE( board.castling().black_queenside );
    // move shall be performable
    REQUIRE( board.move(Field::e8, Field::c8, PieceType::queen) );
    // e8 shall be empty
    REQUIRE( board.element(Field::e8) == Piece() );
    // c8 shall be black king
    REQUIRE( board.element(Field::c8) == Piece(Colour::black, PieceType::king) );
    // a8 shall be empty
    REQUIRE( board.element(Field::a8) == Piece() );
    // d8 shall be black rook
    REQUIRE( board.element(Field::d8) == Piece(Colour::black, PieceType::rook) );
    // Castling for black player is not allowed anymore.
    REQUIRE_FALSE( board.castling().black_kingside );
    REQUIRE_FALSE( board.castling().black_queenside );
    // Black player has castled.
    REQUIRE( board.castling().black_castled == Ternary::true_value );
  }
}

TEST_CASE("Board::halfmovesFifty()")
{
  using namespace simplechess;
  Board board;

  // Initialize board.
  REQUIRE( board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0") );
  // Halfmoves shall be zero.
  REQUIRE( board.halfmovesFifty() == 0 );
  // Move white knight.
  REQUIRE( board.move(Field::b1, Field::a3, PieceType::queen) );
  // Halfmoves shall be one, because there was no capture or pawn move.
  REQUIRE( board.halfmovesFifty() == 1 );
  // Move black knight.
  REQUIRE( board.move(Field::b8, Field::a6, PieceType::queen) );
  // Halfmoves shall be two, because there was no capture or pawn move.
  REQUIRE( board.halfmovesFifty() == 2 );
  // Move white knight.
  REQUIRE( board.move(Field::g1, Field::h3, PieceType::queen) );
  // Halfmoves shall be three, because there was no capture or pawn move.
  REQUIRE( board.halfmovesFifty() == 3 );
  // Move black knight.
  REQUIRE( board.move(Field::g8, Field::h6, PieceType::queen) );
  // Halfmoves shall be four, because there was no capture or pawn move.
  REQUIRE( board.halfmovesFifty() == 4 );
  // Number of halfmoves should be reflected in FEN.
  REQUIRE( ForsythEdwardsNotation::fromBoard(board) ==
    "r1bqkb1r/pppppppp/n6n/8/8/N6N/PPPPPPPP/R1BQKB1R w KQkq - 4"
  );
  // Move white pawn.
  REQUIRE( board.move(Field::e2, Field::e4, PieceType::queen) );
  // Halfmoves shall be back to zero, because that was a pawn move.
  REQUIRE( board.halfmovesFifty() == 0 );
  // Move black pawn.
  REQUIRE( board.move(Field::d7, Field::d5, PieceType::queen) );
  // Halfmoves shall be back to zero, because that was a pawn move.
  REQUIRE( board.halfmovesFifty() == 0 );
  REQUIRE( ForsythEdwardsNotation::fromBoard(board) ==
    "r1bqkb1r/ppp1pppp/n6n/3p4/4P3/N6N/PPPP1PPP/R1BQKB1R w KQkq d6 0"
  );
  // Move white queen.
  REQUIRE( board.move(Field::d1, Field::g4, PieceType::queen) );
  // Halfmoves shall be one, because there was no capture or pawn move.
  REQUIRE( board.halfmovesFifty() == 1 );
  REQUIRE( ForsythEdwardsNotation::fromBoard(board) ==
    "r1bqkb1r/ppp1pppp/n6n/3p4/4P1Q1/N6N/PPPP1PPP/R1B1KB1R b KQkq - 1"
  );
  // Move black bishop to capture queen.
  REQUIRE( board.move(Field::c8, Field::g4, PieceType::queen) );
  // Halfmoves shall be back to zero, because that was a capture.
  REQUIRE( board.halfmovesFifty() == 0 );
  REQUIRE( ForsythEdwardsNotation::fromBoard(board) ==
    "r2qkb1r/ppp1pppp/n6n/3p4/4P1b1/N6N/PPPP1PPP/R1B1KB1R w KQkq - 0"
  );
}
