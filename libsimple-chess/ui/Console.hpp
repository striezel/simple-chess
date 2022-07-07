/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016, 2017, 2022  Dirk Stolle

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

#ifndef SIMPLE_CHESS_CONSOLE_HPP
#define SIMPLE_CHESS_CONSOLE_HPP

#include "../data/Board.hpp"

namespace simplechess::ui
{

/** Shows a chess board on the console using ASCII characters for pieces. */
class Ascii
{
  public:
    /** \brief Prints the board to standard output.
     *
     * \param board   the current chess board
     * \param showLabels  whether to show labels for fields (a-h, 1-8)
     */
    static void showBoard(const Board& board, const bool showLabels);
};

/** Shows a chess board on the console using Unicode symbols for pieces. */
class Symbolic
{
  public:
    /** \brief Prints the board to standard output.
     *
     * \param board   the current chess board
     * \param showLabels  whether to show labels for fields (a-h, 1-8)
     */
    static void showBoard(const Board& board, const bool showLabels);
};


/** \brief Prints the board to standard output.
 *
 * \param board   the current chess board
 * \param PieceToChars   function that translates Piece to character sequence
 * \param showLabels  whether to show labels for fields (a-h, 1-8)
 */
template<typename Fn>
void showBoard(const Board& board, Fn PieceToChars, const bool showLabels)
{
  const std::string rowSeparator = "+---+---+---+---+---+---+---+---+";
  if (showLabels)
  {
    std::cout << "  ";
  }
  std::cout << rowSeparator << "\n";
  for (int r = 8; r >= 1; r--)
  {
    if (showLabels)
    {
      std::cout << std::to_string(r) << ' ';
    }
    std::cout << "| ";
    for (char c = 'a'; c <= 'h'; ++c)
    {
      const Piece & piece = board.element(toField(c, r));
      std::cout << PieceToChars(piece) << " | ";
    } // for c
    std::cout << "\n";
    if (showLabels)
    {
      std::cout << "  ";
    }
    std::cout << rowSeparator << "\n";
  } // for r
  if (showLabels)
  {
    std::cout << "    a   b   c   d   e   f   g   h\n";
  }
}

} // namespace

#endif // SIMPLE_CHESS_CONSOLE_HPP
