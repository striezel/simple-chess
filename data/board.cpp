/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016  Dirk Stolle

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

#include "board.hpp"
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
  m_castling(Castling())
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
    m_castling = Castling();

  //parse info about en passant move
  if (parts.size() > 3)
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
  } //if
  else
    m_enPassant = Field::none;

  // Other info from FEN is not parsed yet, so return true for now.
  return true;
}

} //namespace
