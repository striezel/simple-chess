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
#include <set>
#include "BSON.hpp"
#include "QueryCursor.hpp"
#include "../Convert.hpp"

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
       std::string out;
       if (elem.getString("_id", out))
         boardIds.push_back(out);
       else
         return false;
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
  BSON query;
  if (!query.append("_id", id))
  {
    std::cerr << "Error: Could not append id to BSON object in lmc::Server::getBoard!"
              << std::endl;
    return false;
  }
  if (!query.finish())
  {
    std::cerr << "Error: Could not finish BSON object in lmc::Server::getBoard!"
              << std::endl;
    return false;
  }
  try
  {
    QueryCursor c = conn.query("meteor.boards", query);
    if (!c.next())
    {
      std::cerr << "Error: Board with id \"" << id << "\" was not found!"
                << std::endl;
      return false;
    } //while
    const BSON elem = c.data();
    if (!getBasicBoardData(elem, board))
      return false;
    if (!getBoardFields(id, board))
      return false;
  } //try-c
  catch(const std::exception& ex)
  {
    std::cerr << "Error: An Exception occurred while querying the board content!"
              << std::endl << ex.what() << std::endl;
    return false;
  }
  catch(...)
  {
    std::cerr << "Error: An Exception occurred while querying the board content!"
              << std::endl;
    return false;
  }
  return true;
}

bool Server::getBasicBoardData(const BSON& elem, Board& board)
{
  std::string data;
  //to move
  if (!elem.getString("toMove", data))
    return false;
  Colour toMove = Colour::none;
  if (data == "black")
    toMove = Colour::black;
  else if (data == "white")
    toMove = Colour::white;
  else
  {
    std::cerr << "Error: Found invalid value \"" << data << "\" for toMove in DB!" << std::endl;
    return false;
  }
  if (!board.setToMove(toMove))
    return false;

  //en passant
  BSON dataObject;
  if (!elem.getObject("enPassant", dataObject))
  {
    std::cerr << "Error: Could not find enPassant object in DB!" << std::endl;
    return false;
  }
  Field ep = Field::none;
  //Elements column and row are both null, if no en passant field is set.
  if (!dataObject.isNull("column"))
  {
    std::string epColumn;
    if (!dataObject.getString("column", epColumn))
    {
      std::cerr << "Error: Could not find column in enPassant object in DB!" << std::endl;
      return false;
    }
    if (epColumn.empty())
    {
      std::cerr << "Error: Column in enPassant object in DB is empty!" << std::endl;
      return false;
    }
    int epRow(0);
    if (!dataObject.getInt32("row", epRow))
    {
      std::cerr << "Error: Could not find row in enPassant object in DB!" << std::endl;
      return false;
    }

    try
    {
      ep = toField(epColumn[0], epRow);
    }
    catch (...)
    {
      std::cerr << "Error: Found invalid en passant data (" << epColumn << epRow
                << ") in DB!" << std::endl;
      return false;
    }
  } //if enPassant.column == null
  if (!board.setEnPassant(ep))
  {
    std::cerr << "Error: Could not set en passant field for board!" << std::endl;
    return false;
  }

  //castling
  Castling c;
  if (!elem.getObject("castling", dataObject))
  {
    std::cerr << "Error: Could not find castling object in DB!" << std::endl;
    return false;
  }
  BSON subObject;
  // -- white
  if (!dataObject.getObject("white", subObject))
  {
    std::cerr << "Error: Could not find castling information for white in DB!" << std::endl;
    return false;
  }
  if (!subObject.getBool("kingside", c.white_kingside))
  {
    std::cerr << "Error: Could not get white kingside castling information from DB!" << std::endl;
    return false;
  }
  if (!subObject.getBool("queenside", c.white_queenside))
  {
    std::cerr << "Error: Could not get white queenside castling information from DB!" << std::endl;
    return false;
  }
  // -- black
  if (!dataObject.getObject("black", subObject))
  {
    std::cerr << "Error: Could not find castling information for black in DB!" << std::endl;
    return false;
  }
  if (!subObject.getBool("kingside", c.black_kingside))
  {
    std::cerr << "Error: Could not get black kingside castling information from DB!" << std::endl;
    return false;
  }
  if (!subObject.getBool("queenside", c.black_queenside))
  {
    std::cerr << "Error: Could not get black queenside castling information from DB!" << std::endl;
    return false;
  }
  board.setCastling(c);
  return true;
}

bool Server::getBoardFields(const std::string& id, Board& board)
{
  BSON query;
  if (!query.append("board", id))
  {
    std::cerr << "Error: Could not append board id to BSON object in lmc::Server::getBoardFields!"
              << std::endl;
    return false;
  }
  if (!query.finish())
  {
    std::cerr << "Error: Could not finish BSON object in lmc::Server::getBoardFields!"
              << std::endl;
    return false;
  }
  try
  {
    QueryCursor c = conn.query("meteor.fields", query);
    std::set<Field> fieldsDone;
    while (c.next())
    {
      const BSON elem = c.data();
      std::string pieceDB;
      if (!elem.getString("piece", pieceDB))
      {
        std::cerr << "Error: Could not get piece information of field from DB!" << std::endl;
        return false;
      }
      std::string colourDB;
      if (!elem.getString("colour", colourDB))
      {
        std::cerr << "Error: Could not get colour information of field from DB!" << std::endl;
        return false;
      }
      Piece element = Convert::toPiece(pieceDB, colourDB);
      if (!element.acceptable())
      {
        std::cerr << "Error: Got invalid piece (" << colourDB << " " << pieceDB
                  << ") from DB!" << std::endl;
        return false;
      }
      std::string columnDB;
      if (!elem.getString("column", columnDB))
      {
        std::cerr << "Error: Could not get column information of field from DB!" << std::endl;
        return false;
      }
      int32_t rowDB = 0;
      if (!elem.getInt32("row", rowDB))
      {
        std::cerr << "Error: Could not get row information of field from DB!" << std::endl;
        return false;
      }
      Field f = Convert::toField(columnDB, rowDB);
      if (f == Field::none)
      {
        std::cerr << "Error: Got invalid field (" << columnDB << rowDB
                  << ") from DB!" << std::endl;
        return false;
      }
      //Has the same element already been set?
      if (fieldsDone.find(f) != fieldsDone.end())
      {
        std::cerr << "Error: Information of field " << columnDB << rowDB
                  << " occurs more than once!" << std::endl;
        return false;
      }
      if (!board.setElement(f, element))
      {
        std::cerr << "Error: Could not set field " << columnDB << rowDB
                  << " to " << colourDB << " " << pieceDB << "!" << std::endl;
        return false;
      }
      fieldsDone.insert(f);
    } //while
    if (fieldsDone.size() < 64)
    {
      std::cerr << "Error: Only " << fieldsDone.size() << " of 64 fields have"
                << " been found in the MongoDB!" << std::endl;
      return false;
    }
    return true;
  } //try-c
  catch(const std::exception& ex)
  {
    std::cerr << "Error: An Exception occurred while querying the board content!"
              << std::endl << ex.what() << std::endl;
    return false;
  }
  catch(...)
  {
    std::cerr << "Error: An Exception occurred while querying the board content!"
              << std::endl;
    return false;
  }
}

} //namespace

} //namespace

} //namespace

} //namespace
