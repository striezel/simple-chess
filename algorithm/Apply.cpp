/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
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

#include "Apply.hpp"
#include "../data/ForsythEdwardsNotation.hpp"
#include "../rules/Moves.hpp"

namespace simplechess
{

namespace algorithm
{

bool applyMove(Board& board, const HalfMove& hMove, const Colour toMove)
{
  //Empty move is a no-op.
  if (hMove.empty())
    return true;
  //Player that is to move on board must be identical to half move player.
  if (board.toMove() != toMove)
    return false;
  //treat kingside castling
  if (hMove.kingsideCastling())
  {
    switch (toMove)
    {
      case Colour::white:
           return ((board.element(Field::e1) == Piece(Colour::white, PieceType::king))
               && board.move(Field::e1, Field::g1, PieceType::queen));
      case Colour::black:
           return ((board.element(Field::e8) == Piece(Colour::black, PieceType::king))
               && board.move(Field::e8, Field::g8, PieceType::queen));
      case Colour::none:
           return false;
    } //switch
  } //if kingside castling
  //treat queenside castling
  if (hMove.queensideCastling())
  {
    switch (toMove)
    {
      case Colour::white:
           return ((board.element(Field::e1) == Piece(toMove, PieceType::king))
               && board.move(Field::e1, Field::c1, PieceType::queen));
      case Colour::black:
           return ((board.element(Field::e8) == Piece(toMove, PieceType::king))
               && board.move(Field::e8, Field::c8, PieceType::queen));
      case Colour::none:
           return false;
    } //switch
  } //if queenside castling

  if (hMove.destination() == Field::none)
    return false;
  //find start field on board
  Field from = hMove.origin();
  if (hMove.originType() != pgn::OriginType::full)
  {
    from = findOriginField(board, hMove);
    if (from == Field::none)
      return false;
  }
  //check whether piece on start field matches the piece in half move
  if (Piece(toMove, hMove.piece()) != board.element(from))
    return false;
  //finally apply the move
  // -- TODO: get proper promotion piece!
  return board.move(from, hMove.destination(), PieceType::queen);
}

Field findOriginField(const Board& board, const HalfMove& hMove)
{
  if (hMove.empty() || (hMove.piece() == PieceType::none))
    return Field::none;

  const Piece piece = Piece(board.toMove(), hMove.piece());
  std::vector<Field> possibleOrigins = findPieces(board, piece);
  for (int i = possibleOrigins.size() - 1; i >= 0; --i)
  {
    bool allowed = false;
    //If move is allowed, then it is a potential matching origin.
    if (Moves::allowed(board, possibleOrigins[i], hMove.destination()))
    {
      const auto ot = hMove.originType();
      // It is only a proper origin, if either files match for a file-only
      // origin or ranks match for a rank-only origin, or the origin was not
      // given at all. In that case there is only one possibility.
      if ((ot == pgn::OriginType::none)
        || ((ot == pgn::OriginType::file) && sameFile(possibleOrigins[i], hMove.origin()))
        || ((ot == pgn::OriginType::rank) && sameRank(possibleOrigins[i], hMove.origin())))
        allowed = true;
    } //if move is allowed
    //Remove field, if it is not allowed to move from there to destination.
    if (!allowed)
      possibleOrigins.erase(possibleOrigins.begin() + i);
  } //for
  if (possibleOrigins.size() == 1)
    return possibleOrigins.front();
  //There are either no matching fields or two or more matching fields. In both
  // cases that indicates that the half move is invalid.
  return Field::none;
}

std::vector<Field> findPieces(const Board& board, const Piece& piece)
{
  std::vector<Field> result;
  Field f = board.findNext(piece, Field::a1);
  while (f != Field::none)
  {
    result.push_back(f);
    //If we already are at the last field, return.
    if (Field::h8 == f)
      return result;
    f = board.findNext(piece, static_cast<Field>(static_cast<int>(f) + 1));
  } //while
  return result;
}

bool checkPortableGameNotation(const PortableGameNotation& pgn)
{
  //check move number range
  const auto min = pgn.firstMoveNumber();
  if (min == 0)
    return false;
  const auto max = pgn.lastMoveNumber();
  if (max == 0)
    return false;
  for(auto i = min; i <= max; ++i)
  {
    if (!pgn.hasMove(i))
      return false;
  } //for
  std::string fen = pgn.tag("FEN");
  if (fen.empty())
    fen = FEN::defaultInitialPosition;
  Board board;
  if (!board.fromFEN(fen))
    return false;
  for (unsigned int i = min; i <= max; ++i)
  {
    const auto moves = pgn.move(i);
    if (!simplechess::algorithm::applyMove(board, moves.first, simplechess::Colour::white))
      return false;
    if (!simplechess::algorithm::applyMove(board, moves.second, simplechess::Colour::black))
      return false;
  } //for
  //All seems to be OK.
  return true;
}

} //namespace

} //namespace
