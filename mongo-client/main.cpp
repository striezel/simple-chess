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
  return 0;
}
