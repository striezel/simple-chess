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

#include "Server.hpp"
#include <iostream>
#include <stdexcept>
#include "BSON.hpp"
#include "QueryCursor.hpp"

namespace simplechess
{

namespace db
{

namespace mongo
{

namespace libmongoclient
{

Server::Server(const std::string& hostname, const uint16_t port, const bool slaveAcceptable)
: conn(hostname, port, slaveAcceptable)
{

}

Server::~Server()
{
  //Nothing to do here, connection object takes care of itself in destructor.
}

bool Server::boardList(std::vector<std::string>& boardIds)
{
   BSON query;
   if (!query.finish())
   {
     std::cerr << "Error: Could not finish BSON object in lmc::Server::boardList!"
               << std::endl;
     return false;
   }
   try
   {
     QueryCursor c = conn.query("meteor.boards", query);
     boardIds.clear();
     while (c.next())
     {
       const BSON elem = c.data();
       //TODO!
       throw std::runtime_error("lmc::Server::boardList() is not implemented yet!");
     } //while
   } //try-c
   catch(const std::exception& ex)
   {
     std::cerr << "Error: An Exception occurred while querying the list of board IDs!"
               << std::endl << ex.what() << std::endl;
     return false;
   }
   catch(...)
   {
     std::cerr << "Error: An Exception occurred while querying the list of board IDs!"
               << std::endl;
     return false;
   }
   return true;
}

bool Server::getBoard(const std::string& id, Board& board)
{
  throw std::runtime_error("Server::getBoard() is not implemented yet!");
}

} //namespace

} //namespace

} //namespace

} //namespace
