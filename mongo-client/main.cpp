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

int main()
{
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
  return 0;
}
