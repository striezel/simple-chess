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

#include <iostream>
#include "../data/ForsythEdwardsNotation.hpp"
#include "../db/mongo/libmongoclient/Server.hpp"
#include "../ui/Console.hpp"

int main(int argc, char** argv)
{
  std::string boardId;
  if ((argc > 1) && (argv[1] != nullptr))
  {
    boardId = std::string(argv[1]);
  }
  simplechess::db::mongo::libmongoclient::Server server("localhost", 3001, true);
  std::cout << "Connection attempt succeeded." << std::endl;
  std::vector<std::string> boards;
  if (!server.boardList(boards))
  {
    std::cerr << "Could not get board list from DB!" << std::endl;
    return 1;
  }
  std::cout << "List of board IDs:" << std::endl;
  for (const auto & id : boards)
  {
    std::cout << "  " << id << std::endl;
  }
  if (boards.empty())
  {
    std::cout << "  No boards are available in the database." << std::endl;
    return 0;
  }

  //Just use the first board, if none is given.
  if (boardId.empty())
    boardId = boards[0];

  simplechess::Board board;
  if (!server.getBoard(boardId, board))
  {
    std::cerr << "Could not get board data for board " << boardId
              << " from DB!" << std::endl;
    return 1;
  }
  std::cout << "Board data retrieval for " << boardId << " succeeded."
            << " (Pass a board ID as 1st argument to this program, if you want"
            << " to see a different board.)" << std::endl;
  simplechess::ui::Console::showBoard(board);


  if (board.element(simplechess::Field::a2) == simplechess::Piece(simplechess::Colour::white, simplechess::PieceType::pawn))
  {
    board.move(simplechess::Field::a2, simplechess::Field::a4, simplechess::PieceType::queen);
    const auto a4 = board.element(simplechess::Field::a4);
    std::cout << "a4: " << a4.colour << " " << a4.piece << "\n";
  }
  if (server.updateBoard(boardId, board))
  {
    std::cout << "Update was successful.\n";
  }

  //insert board
  if (!board.fromFEN(simplechess::FEN::defaultInitialPosition))
  {
    std::cerr << "Could not initialize board from FEN!" << std::endl;
    return 1;
  }
  const auto newBoardId = server.insertBoard(board);
  if (newBoardId.empty())
  {
    std::cerr << "Could not insert new board!" << std::endl;
    return 1;
  }
  std::cout << "Success. New board's ID is " << newBoardId << "." << std::endl;
  return 0;
}
