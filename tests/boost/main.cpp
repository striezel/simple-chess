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
#define BOOST_TEST_MODULE simpleChess
#include <boost/test/unit_test.hpp>

#include "../../data/Board.hpp"
#include "../../data/ForsythEdwardsNotation.hpp"
#include "../../pgn/Tokenizer.hpp"

BOOST_AUTO_TEST_SUITE(FEN)

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

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(PGN)

BOOST_AUTO_TEST_CASE(defaultExampleTokenizer)
{
  const std::string example =
    std::string("[Event \"F/S Return Match\"]\n")
    + "[Site \"Belgrade, Serbia JUG\"]\n"
    + "[Date \"1992.11.04\"]\n"
    + "[Round \"29\"]\n"
    + "[White \"Fischer, Robert J.\"]\n"
    + "[Black \"Spassky, Boris V.\"]\n"
    + "[Result \"1/2-1/2\"]\n"
    + "\n"
    + "1. e4 e5 2. Nf3 Nc6 3. Bb5 a6 4. Ba4 Nf6 5. O-O Be7 6. Re1 b5 7. Bb3 d6 8. c3\n"
    + "O-O 9. h3 Nb8 10. d4 Nbd7 11. c4 c6 12. cxb5 axb5 13. Nc3 Bb7 14. Bg5 b4 15.\n"
    + "Nb1 h6 16. Bh4 c5 17. dxe5 Nxe4 18. Bxe7 Qxe7 19. exd6 Qf6 20. Nbd2 Nxd6 21.\n"
    + "Nc4 Nxc4 22. Bxc4 Nb6 23. Ne5 Rae8 24. Bxf7+ Rxf7 25. Nxf7 Rxe1+ 26. Qxe1 Kxf7\n"
    + "27. Qe3 Qg5 28. Qxg5 hxg5 29. b3 Ke6 30. a3 Kd6 31. axb4 cxb4 32. Ra5 Nd5 33.\n"
    + "f3 Bc8 34. Kf2 Bf5 35. Ra7 g6 36. Ra6+ Kc5 37. Ke1 Nf4 38. g3 Nxh3 39. Kd2 Kb5\n"
    + "40. Rd6 Kc5 41. Ra6 Nf2 42. g4 Bd3 43. Re6 1/2-1/2\n";

  std::vector<simplechess::pgn::Token> tokens;
  bool success = simplechess::pgn::Tokenizer::fromString(example, tokens);
  //parsing should be successful
  BOOST_REQUIRE(success);
  //first token is left square bracket
  BOOST_REQUIRE(simplechess::pgn::TokenType::LeftBracket == tokens.front().type);
  //last token is game end
  BOOST_REQUIRE(simplechess::pgn::TokenType::GameEnd == tokens.back().type);
  BOOST_REQUIRE(std::string("1/2-1/2") == tokens.back().text);
}

BOOST_AUTO_TEST_SUITE_END()
