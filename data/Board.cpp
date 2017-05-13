/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016, 2017  Dirk Stolle

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

#include "Board.hpp"
#include <cmath>
#include "../rules/check.hpp"
#include "../rules/Moves.hpp"
#include "../util/strings.hpp"

namespace simplechess
{

/** \brief returns the next column for a given column
 *
 * \param character that denotes the current column
 * \return Returns the character for the next column.
 * If the given column is out of range, the function will return 'a'.
 */
char nextColumn(const char column)
{
  char nextCol = static_cast<char>(column + 1);
  if ((nextCol > 'h') || (nextCol < 'a'))
  {
    nextCol = 'a';
  }
  return nextCol;
}


Board::Board()
: m_toMove(Colour::white),
  m_enPassant(Field::none),
  m_castling(Castling()),
  m_blackInCheck(false),
  m_whiteInCheck(false)
{
  for(int i = static_cast<int>(Field::a1); i <= static_cast<int>(Field::h8); ++i)
  {
    m_Fields[static_cast<Field>(i)] = Piece();
  }
}

const Piece& Board::element(const Field f) const
{
  const std::map<Field, Piece>::const_iterator cIter = m_Fields.find(f);
  if (cIter != m_Fields.end())
    return cIter->second;
  throw std::runtime_error("Field does not exist on board!");
}

const Colour& Board::toMove() const
{
  return m_toMove;
}

const Field& Board::enPassant() const
{
  return m_enPassant;
}

const Castling& Board::castling() const
{
  return m_castling;
}

bool Board::isInCheck(const Colour colour) const
{
  switch(colour)
  {
    case Colour::white:
         return m_whiteInCheck;
    case Colour::black:
         return m_blackInCheck;
    default:
         //"None" can never be in check.
         return false;
  } //switch
}

bool Board::fromFEN(const std::string& FEN)
{
  //split into single parts
  const std::vector<std::string> parts = util::split(FEN, ' ');
  if (parts.empty())
    return false;
  //first part: pieces on board
  const std::map<char, Piece> fenmap = {
    { 'r', Piece(Colour::black, PieceType::rook)},
    { 'n', Piece(Colour::black, PieceType::knight)},
    { 'b', Piece(Colour::black, PieceType::bishop)},
    { 'q', Piece(Colour::black, PieceType::queen)},
    { 'k', Piece(Colour::black, PieceType::king)},
    { 'p', Piece(Colour::black, PieceType::pawn)},

    { 'R', Piece(Colour::white, PieceType::rook)},
    { 'N', Piece(Colour::white, PieceType::knight)},
    { 'B', Piece(Colour::white, PieceType::bishop)},
    { 'Q', Piece(Colour::white, PieceType::queen)},
    { 'K', Piece(Colour::white, PieceType::king)},
    { 'P', Piece(Colour::white, PieceType::pawn)}
  };

  const std::vector<std::string> rows = util::split(parts[0], '/');
  if (rows.size() != 8)
    return false;
  int boardRow = 8;
  for(const std::string& singleRow : rows)
  {
    char boardColumn = 'a';
    for (unsigned int j = 0; j < singleRow.size(); ++j)
    {
      const auto iter = fenmap.find(singleRow[j]);
      if (iter != fenmap.end())
      {
        m_Fields[toField(boardColumn, boardRow)] = iter->second;
        boardColumn = nextColumn(boardColumn);
      } //if
      else if ((singleRow[j] >= '1') && (singleRow[j] <= '8'))
      {
        const auto count = singleRow[j] - '1' + 1;
        for (int k = 1; k <= count; ++k)
        {
          m_Fields[toField(boardColumn, boardRow)] = Piece(Colour::none, PieceType::none);
          boardColumn = nextColumn(boardColumn);
        }
      } //else if '1'..'8'
      else
      {
        //invalid character
        return false;
      }
    } //for j
    boardRow = boardRow - 1;
  } //for

  //Who is to move?
  if (parts.size() > 1)
  {
    if (parts[1] == "b")
      m_toMove = Colour::black;
    else
      m_toMove = Colour::white;
  }
  else
    m_toMove = Colour::white;

  //Info about castling?
  if (parts.size() > 2)
  {
    m_castling.fromFEN(parts[2]);
  }
  else
  {
    m_castling = Castling();
    //guess as good as possible from current position
    if (element(Field::e1) == Piece(Colour::white, PieceType::king))
    {
      m_castling.white_kingside = element(Field::h1) == Piece(Colour::white, PieceType::rook);
      m_castling.white_queenside = element(Field::a1) == Piece(Colour::white, PieceType::rook);
    }
    else
    {
      m_castling.white_kingside = false;
      m_castling.white_queenside = false;
    }
    if (element(Field::e8) == Piece(Colour::black, PieceType::king))
    {
      m_castling.black_kingside = element(Field::h8) == Piece(Colour::black, PieceType::rook);
      m_castling.black_queenside = element(Field::a8) == Piece(Colour::black, PieceType::rook);
    }
    else
    {
      m_castling.black_kingside = false;
      m_castling.black_queenside = false;
    }
  } //castling


  //parse info about en passant move
  if (parts.size() > 3)
  {
    if (parts[3] == "-")
    {
      m_enPassant = Field::none;
    }
    else
    {
      try
      {
        m_enPassant = toField(parts[3][0], parts[3][0] - '1' + 1);
        if ((row(m_enPassant) != 3) && (row(m_enPassant) != 6))
          return false;
      }
      catch(...)
      {
        return false;
      }
    } //else
  } //if
  else
    m_enPassant = Field::none;

  //update info who is in check
  m_whiteInCheck = simplechess::isInCheck(*this, Colour::white);
  m_blackInCheck = simplechess::isInCheck(*this, Colour::black);

  // Other info from FEN is not parsed yet, so return true for now.
  return true;
}

bool Board::move(const Field from, const Field to, PieceType promoteTo)
{
  if ((from == Field::none) || (to == Field::none))
    return false;

  const Piece start = element(from);
  //Is the correct player moving?
  if (toMove() != start.colour)
  {
    return false;
  }

  const bool allow = Moves::allowed(*this, from, to);
  if (!allow)
    return false;
  //save for possible later use
  const Piece dest = element(to);

  // Move is allowed.
  // -- "copy" piece to destination field
  m_Fields[to] = start;
  // -- remove piece in start field
  m_Fields[from] = Piece(Colour::none, PieceType::none);
  // holds en passant data for next move
  Field enPassantData = Field::none;
  // -- check for special moves of pawn pieces
  if (start.piece == PieceType::pawn)
  {
    // check for promotion
    // -- sanitize promotion piece
    Moves::sanitizePromotion(promoteTo);
    // -- check for promotion of white pawn
    if ((start.colour == Colour::white) && (row(to) == 8))
    {
      m_Fields[to].piece = promoteTo;
      //console.log('Info: Promoted white pawn on ' + column(to) + row(to) + ' to ' + promoteTo + '.');
    }
    // -- check for promotion of black pawn
    else if ((start.colour == Colour::black) && (row(to) == 1))
    {
       m_Fields[to].piece = promoteTo;
      //console.log('Info: Promoted black pawn on ' + column(to) + row(to) + ' to ' + promoteTo + '.');
    }
    // check for en passant capture
    else if (to == enPassant())
    {
      int colDiff = std::abs(column(from) - column(to));
      int rowDiff = std::abs(row(to) - row(from));
      if ((colDiff == 1) && (rowDiff == 1))
      {
        //remove captured pawn
        int removeRow = row(to);
        if (removeRow == 3)
          removeRow = 4;
        else
          removeRow = 5;
        m_Fields[toField(column(to), removeRow)] = Piece(Colour::none, PieceType::none);
      } //if
    } //if en passant field is destination
    //check whether en passant capture is possible in next move
    if ((start.colour == Colour::white) && (row(from) == 2) && (row(to) == 4))
      enPassantData = toField(column(from), 3);
    else if ((start.colour == Colour::black) && (row(from) == 7) && (row(to) == 5))
      enPassantData = toField(column(from), 6);
  }//if pawn
  // -- check for castling move
  if (start.piece == PieceType::king)
  {
    if ((start.colour == Colour::white) && (from == Field::e1))
    {
      if ((to == Field::c1) && (dest.piece == PieceType::none))
      {
        //white queenside castling
        // King was already moved, we just have to move the rook here.
        m_Fields[Field::a1] = Piece(Colour::none, PieceType::none);
        m_Fields[Field::d1] = Piece(Colour::white, PieceType::rook);
      }
      if ((to == Field::g1) && (dest.piece == PieceType::none))
      {
        //white kingside castling
        // King was already moved, we just have to move the rook here.
        m_Fields[Field::h1] = Piece(Colour::none, PieceType::none);
        m_Fields[Field::f1] = Piece(Colour::white, PieceType::rook);
      }
    }//if white king at initial position
    else if ((start.colour == Colour::black) && (from == Field::e8))
    {
      if ((to == Field::c8) && (dest.piece == PieceType::none))
      {
        //black queenside castling
        // King was already moved, we just have to move the rook here.
        m_Fields[Field::a8] = Piece(Colour::none, PieceType::none);
        m_Fields[Field::d8] = Piece(Colour::black, PieceType::rook);
      }
      if ((to == Field::g8) && (dest.piece == PieceType::none))
      {
        //black kingside castling
        // King was already moved, we just have to move the rook here.
        m_Fields[Field::h8] = Piece(Colour::none, PieceType::none);
        m_Fields[Field::f8] = Piece(Colour::black, PieceType::rook);
      }
    }//if black king at initial position
  } //if king may be castling
  // -- castling update
  if (start.piece == PieceType::king)
  {
    if (start.colour == Colour::black)
    {
      m_castling.black_kingside = false;
      m_castling.black_queenside = false;
    }
    else
    {
      m_castling.white_kingside = false;
      m_castling.white_queenside = false;
    }
  } //if king
  else if (start.piece == PieceType::rook)
  {
    if (start.colour == Colour::black)
    {
      if (from == Field::a8)
        m_castling.black_queenside = false;
      else if (from == Field::h8)
        m_castling.black_kingside = false;
    } //if black rook moved
    else if (start.colour == Colour::white)
    {
      if (from == Field::a1)
        m_castling.white_queenside = false;
      else if (from == Field::h1)
        m_castling.white_kingside = false;
    } //if white rook moved
  } //if rook
  // -- update en passant data
  m_enPassant = enPassantData;
  // -- determine whether anyone is in check
  const bool whiteCheck = simplechess::isInCheck(*this, Colour::white);
  /* if (whiteCheck && m_whiteInCheck)
    Boards.update({_id: board._id}, {$set: {winner: 'black'}}); */
  m_whiteInCheck = whiteCheck;
  const bool blackCheck = simplechess::isInCheck(*this, Colour::black);
  /* if (blackCheck && m_blackInCheck)
    Boards.update({_id: board._id}, {$set: {winner: 'white'}}); */
  m_blackInCheck = blackCheck;
  //TODO: check for checkmate
  // -- update colour that is to move
  if (m_toMove == Colour::white)
    m_toMove = Colour::black;
  else
    m_toMove = Colour::white;
  return true;
}

} //namespace
