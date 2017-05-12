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

#include <iostream>
#include "../data/board.hpp"
#include "../ui/Console.hpp"


/** \brief prints a board to the standard output
 *
 * \param board   the chess board
 */
void showBoard(const simplechess::Board& board)
{
  simplechess::ui::Console::showBoard(board);
  std::cout << "\n";
  if (board.toMove() == simplechess::Colour::white)
    std::cout << "White is to move.\n";
  else
    std::cout << "Black is to move.\n";
}


/** \brief gets a field from the standard input
 *
 * \return Returns the field that was entered by the user.
 */
simplechess::Field getField()
{
  std::string input;
  std::cin >> input;
  if (input.size() < 2)
    input = "a1";
  char c = input[0];
  int r = input[1] - '1' + 1;
  return simplechess::toField(c, r);
}


int main(int argc, char** argv)
{
  simplechess::Board board;
  if ((argc > 1) && (argv != nullptr))
  {
    const std::string fenString = std::string(argv[1]);
    if (!board.fromFEN(fenString))
    {
      std::cerr << "Could not initialize board from FEN string \"" << fenString
                << "\"!\n";
      return 1;
    }
  } //if one argument is given
  else
  {
    //use default start position
    if (!board.fromFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"))
    {
      std::cerr << "Could not initialize board from FEN string!\n";
      return 1;
    }
  } //else

  //potentially endless game loop
  while (true)
  {
    showBoard(board);
    std::cout << "\n"
              << "Your move starts from field: ";
    const simplechess::Field start = getField();
    std::cout << "Your move goes to field: ";
    const simplechess::Field destination = getField();
    if (!board.move(start, destination, simplechess::PieceType::queen))
    {
      std::cout << "The move is not allowed!\n";
      return 2;
    }
  } //while

  return 0;
}
