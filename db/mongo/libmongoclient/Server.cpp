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
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <set>
#include "BSON.hpp"
#include "QueryCursor.hpp"
#include "../Convert.hpp"
#include "../IdGenerator.hpp"

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
     } // while
   } // try-c
   catch(const std::exception& ex)
   {
     std::cerr << "Error: An exception occurred while querying the list of board IDs!"
               << std::endl << ex.what() << std::endl;
     return false;
   }
   catch(...)
   {
     std::cerr << "Error: An error occurred while querying the list of board IDs!"
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
    } // while
    const BSON elem = c.data();
    if (!getBasicBoardData(elem, board))
      return false;
    if (!getBoardFields(id, board))
      return false;
  } // try-c
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
  // to move
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

  // en passant
  BSON dataObject;
  if (!elem.getObject("enPassant", dataObject))
  {
    std::cerr << "Error: Could not find enPassant object in DB!" << std::endl;
    return false;
  }
  Field ep = Field::none;
  // Elements column and row are both null, if no en passant field is set.
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
    int32_t epRow(0);
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
  } // if enPassant.column == null
  if (!board.setEnPassant(ep))
  {
    std::cerr << "Error: Could not set en passant field for board!" << std::endl;
    return false;
  }

  // castling
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
      const Field f = Convert::toField(columnDB, rowDB);
      if (f == Field::none)
      {
        std::cerr << "Error: Got invalid field (" << columnDB << rowDB
                  << ") from DB!" << std::endl;
        return false;
      }
      // Has the same element already been set?
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
    } // while
    if (fieldsDone.size() < 64)
    {
      std::cerr << "Error: Only " << fieldsDone.size() << " of 64 fields have"
                << " been found in the MongoDB!" << std::endl;
      return false;
    }
    return true;
  } // try-c
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

std::string Server::insertBasicBoardData(const Board& board)
{
  // build insert object
  BSON document;
  std::vector<std::string> idList;
  if (!boardList(idList))
  {
    std::cerr << "Error: Could not get existing IDs in lmc::Server::insertBasicBoardData!"
             << std::endl;
    return std::string();
  }
  const std::string id = IdGenerator::generate(idList);
  if (!document.append("_id", id))
  {
    std::cerr << "Error: Could not append ID to BSON object in lmc::Server::insertBasicBoardData!"
             << std::endl;
    return std::string();
  }
  if (!document.append("toMove", Convert::colourToMongoDbString(board.toMove())))
  {
    std::cerr << "Error: Could not append toMove to BSON object in lmc::Server::insertBasicBoardData!"
             << std::endl;
    return std::string();
  }
  // Get milliseconds since epoch.
  const std::chrono::milliseconds msse = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
  if (!document.append("created", msse))
  {
    std::cerr << "Error: Could not append created to BSON object in lmc::Server::insertBasicBoardData!"
             << std::endl;
    return std::string();
  }
  // build castling object
  BSON castling;
  {
    const Castling& c = board.castling();
    BSON white;
    if (!white.append("kingside", c.white_kingside) || !white.append("queenside", c.white_queenside))
    {
      std::cerr << "Error: Could not append white castling data to BSON object in lmc::Server::insertBasicBoardData!"
                << std::endl;
      return std::string();
    }
    if (!white.finish())
    {
      std::cerr << "Error: Could not finish BSON object (white) in lmc::Server::insertBasicBoardData!"
                << std::endl;
      return std::string();
    }
    BSON black;
    if (!black.append("kingside", c.black_kingside) || !black.append("queenside", c.black_queenside))
    {
      std::cerr << "Error: Could not append black castling data to BSON object in lmc::Server::insertBasicBoardData!"
                << std::endl;
      return std::string();
    }
    if (!black.finish())
    {
      std::cerr << "Error: Could not finish BSON object (black) in lmc::Server::insertBasicBoardData!"
                << std::endl;
      return std::string();
    }
    if (!castling.append("white", white) || !castling.append("black", black))
    {
      std::cerr << "Error: Could not append BSON objects to castling data in lmc::Server::insertBasicBoardData!"
                << std::endl;
      return std::string();
    }
  } // end of scope
  if (!castling.finish())
  {
    std::cerr << "Error: Could not finish BSON object (castling) in lmc::Server::insertBasicBoardData!"
              << std::endl;
    return std::string();
  }
  // build check object
  BSON check;
  if (!check.append("white", board.isInCheck(Colour::white)))
  {
    std::cerr << "Error: Could not append white to BSON object in lmc::Server::insertBasicBoardData!"
              << std::endl;
    return std::string();
  }
  if (!check.append("black", board.isInCheck(Colour::black)))
  {
    std::cerr << "Error: Could not append black to BSON object in lmc::Server::insertBasicBoardData!"
              << std::endl;
    return std::string();
  }
  if (!check.finish())
  {
    std::cerr << "Error: Could not finish BSON object (check) in lmc::Server::insertBasicBoardData!"
              << std::endl;
    return std::string();
  }
  // build en passant object
  BSON enPassant;
  if (board.enPassant() == Field::none)
  {
    if (!enPassant.appendNull("column") || !enPassant.appendNull("row"))
    {
      std::cerr << "Error: Could not append column and row to BSON object in lmc::Server::insertBasicBoardData!"
                << std::endl;
      return std::string();
    }
  }
  else
  {
    if (!enPassant.append("column", std::string(1, column(board.enPassant()))))
    {
      std::cerr << "Error: Could not append column to BSON object in lmc::Server::insertBasicBoardData!"
                << std::endl;
      return std::string();
    }
    if (!enPassant.append("row", row(board.enPassant())))
    {
      std::cerr << "Error: Could not append row to BSON object in lmc::Server::insertBasicBoardData!"
                << std::endl;
      return std::string();
    }
  } // else
  if (!enPassant.finish())
  {
    std::cerr << "Error: Could not finish BSON object (enPassant) in lmc::Server::insertBasicBoardData!"
              << std::endl;
    return std::string();
  }
  // append all objects to subUpdate
  if (!document.append("castling", castling))
  {
    std::cerr << "Error: Could not append castling to BSON object in lmc::Server::insertBasicBoardData!"
              << std::endl;
    return std::string();
  }
  if (!document.append("check", check))
  {
    std::cerr << "Error: Could not append check to BSON object in lmc::Server::insertBasicBoardData!"
              << std::endl;
    return std::string();
  }
  if (!document.append("enPassant", enPassant))
  {
    std::cerr << "Error: Could not append enPassant to BSON object in lmc::Server::insertBasicBoardData!"
              << std::endl;
    return std::string();
  }
  if (!document.appendNull("winner"))
  {
    std::cerr << "Error: Could not append winner to BSON object in lmc::Server::insertBasicBoardData!"
              << std::endl;
    return std::string();
  }
  if (!document.finish())
  {
    std::cerr << "Error: Could not finish BSON object (document) in lmc::Server::insertBasicBoardData!"
              << std::endl;
    return std::string();
  }
  if (!conn.insert("meteor.boards", document))
  {
    std::cerr << "Error: Could not insert BSON document in lmc::Server::insertBasicBoardData!"
              << std::endl;
    return std::string();
  }
  // return board ID
  return id;
}

std::string Server::insertBoard(const Board& board)
{
  std::string boardId = insertBasicBoardData(board);
  if (boardId.empty())
    return "";
  // insert fields
  for (char col = 'a'; col <= 'h'; ++col)
  {
    for (int r = 1; r <= 8; ++r)
    {
      BSON document;
      const std::string fieldId = IdGenerator::generate();
      if (!document.append("_id", fieldId))
      {
        std::cerr << "Error: Could not append _id to BSON object in lmc::Server::insertBoard!"
                  << std::endl;
        return "";
      }
      if (!document.append("board", boardId))
      {
        std::cerr << "Error: Could not append board id to BSON object in lmc::Server::insertBoard!"
                  << std::endl;
        return "";
      }
      const auto& elem = board.element(toField(col, r));
      if (!document.append("piece", Convert::pieceToString(elem.piece)))
      {
        std::cerr << "Error: Could not append piece to BSON object in lmc::Server::insertBoard!"
                  << std::endl;
        return "";
      }
      if (!document.append("colour", Convert::colourToMongoDbString(elem.colour)))
      {
        std::cerr << "Error: Could not append colour to BSON object in lmc::Server::insertBoard!"
                  << std::endl;
        return "";
      }
      if (!document.append("column", std::string(1, col)))
      {
        std::cerr << "Error: Could not append column to BSON object in lmc::Server::insertBoard!"
                  << std::endl;
        return "";
      }
      if (!document.append("row", r))
      {
        std::cerr << "Error: Could not append row to BSON object in lmc::Server::insertBoard!"
                  << std::endl;
        return "";
      }
      if (!document.finish())
      {
        std::cerr << "Error: Could not finish BSON object in lmc::Server::insertBoard!"
                  << std::endl;
        return "";
      }
      if (!conn.insert("meteor.fields", document))
      {
        std::cerr << "Error: Could not insert document into database lmc::Server::insertBoard!"
                  << std::endl;
        return "";
      }
    } // for row
  } // for column
  return boardId;
}

bool Server::updateBoard(const std::string& id, const Board& board)
{
  BSON query;
  if (!query.append("_id", id))
  {
    std::cerr << "Error: Could not append id to BSON object in lmc::Server::setBoard!"
              << std::endl;
    return false;
  }
  if (!query.finish())
  {
    std::cerr << "Error: Could not finish BSON object in lmc::Server::setBoard!"
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
    } // while
    if (!updateBasicBoardData(id, board))
      return false;
    if (!updateBoardFields(id, board))
      return false;
  } // try-c
  catch(const std::exception& ex)
  {
    std::cerr << "Error: An Exception occurred while setting the board content!"
              << std::endl << ex.what() << std::endl;
    return false;
  }
  catch(...)
  {
    std::cerr << "Error: An Exception occurred while setting the board content!"
              << std::endl;
    return false;
  }
  return true;
}

bool Server::updateFieldOnBoard(const std::string& id, const Board& board, const Field f)
{
  if ((f == Field::none) || id.empty())
    return false;

  const int fieldRow = row(f);
  const std::string fieldColumn = std::string(1, column(f));

  BSON selector;
  if (!selector.append("board", id))
  {
    std::cerr << "Error: Could not append board id to BSON object in lmc::Server::updateFieldOnBoard!"
              << std::endl;
    return false;
  }
  if (!selector.append("column", fieldColumn))
  {
    std::cerr << "Error: Could not append column to BSON object in lmc::Server::updateFieldOnBoard!"
              << std::endl;
    return false;
  }
  if (!selector.append("row", fieldRow))
  {
    std::cerr << "Error: Could not append row to BSON object in lmc::Server::updateFieldOnBoard!"
              << std::endl;
    return false;
  }
  if (!selector.finish())
  {
    std::cerr << "Error: Could not finish BSON object in lmc::Server::updateFieldOnBoard!"
              << std::endl;
    return false;
  }

  const auto & elem = board.element(f);
  BSON subUpdate;
  if (!subUpdate.append("piece", Convert::pieceToString(elem.piece)))
  {
    std::cerr << "Error: Could not append piece to BSON object in lmc::Server::updateFieldOnBoard!"
              << std::endl;
    return false;
  }
  if (!subUpdate.append("colour", Convert::colourToMongoDbString(elem.colour)))
  {
    std::cerr << "Error: Could not append colour to BSON object in lmc::Server::updateFieldOnBoard!"
              << std::endl;
    return false;
  }
  if (!subUpdate.finish())
  {
    std::cerr << "Error: Could not finish BSON object (subUpdate) in lmc::Server::updateFieldOnBoard!"
              << std::endl;
    return false;
  }

  BSON update;
  if (!update.append("$set", subUpdate))
  {
    std::cerr << "Error: Could not append document to BSON object in lmc::Server::updateFieldOnBoard!"
              << std::endl;
    return false;
  }
  if (!update.finish())
  {
    std::cerr << "Error: Could not finish BSON object (update) in lmc::Server::updateFieldOnBoard!"
              << std::endl;
    return false;
  }


  try
  {
    return conn.update("meteor.fields", selector, update);
  } // try-c
  catch(const std::exception& ex)
  {
    std::cerr << "Error: An exception occurred while updating a field on the board!"
              << std::endl << ex.what() << std::endl;
    return false;
  }
  catch(...)
  {
    std::cerr << "Error: An error occurred while updating a field on the board!"
              << std::endl;
    return false;
  }
}

bool Server::updateBasicBoardData(const std::string& id, const Board& board)
{
  BSON selector;
  if (!selector.append("_id", id))
  {
    std::cerr << "Error: Could not append _id to BSON object in lmc::Server::setBasicBoardData!"
              << std::endl;
    return false;
  }
  if (!selector.finish())
  {
    std::cerr << "Error: Could not finish BSON object in lmc::Server::setBasicBoardData!"
              << std::endl;
    return false;
  }

  // build sub update object
  BSON subUpdate;
  if (!subUpdate.append("toMove", Convert::colourToMongoDbString(board.toMove())))
  {
    std::cerr << "Error: Could not append toMove to BSON object in lmc::Server::setBasicBoardData!"
             << std::endl;
    return false;
  }
  // build castling object
  BSON castling;
  {
    const Castling& c = board.castling();
    BSON white;
    if (!white.append("kingside", c.white_kingside) || !white.append("queenside", c.white_queenside))
    {
      std::cerr << "Error: Could not append white castling data to BSON object in lmc::Server::setBasicBoardData!"
                << std::endl;
      return false;
    }
    if (!white.finish())
    {
      std::cerr << "Error: Could not finish BSON object (white) in lmc::Server::setBasicBoardData!"
                << std::endl;
      return false;
    }
    BSON black;
    if (!black.append("kingside", c.black_kingside) || !black.append("queenside", c.black_queenside))
    {
      std::cerr << "Error: Could not append black castling data to BSON object in lmc::Server::setBasicBoardData!"
                << std::endl;
      return false;
    }
    if (!black.finish())
    {
      std::cerr << "Error: Could not finish BSON object (black) in lmc::Server::setBasicBoardData!"
                << std::endl;
      return false;
    }
    if (!castling.append("white", white) || !castling.append("black", black))
    {
      std::cerr << "Error: Could not append BSON objects to castling data in lmc::Server::setBasicBoardData!"
                << std::endl;
      return false;
    }
  } // end of scope
  if (!castling.finish())
  {
    std::cerr << "Error: Could not finish BSON object (castling) in lmc::Server::setBasicBoardData!"
              << std::endl;
    return false;
  }
  // build check object
  BSON check;
  if (!check.append("white", board.isInCheck(Colour::white)))
  {
    std::cerr << "Error: Could not append white to BSON object in lmc::Server::setBasicBoardData!"
              << std::endl;
    return false;
  }
  if (!check.append("black", board.isInCheck(Colour::black)))
  {
    std::cerr << "Error: Could not append black to BSON object in lmc::Server::setBasicBoardData!"
              << std::endl;
    return false;
  }
  if (!check.finish())
  {
    std::cerr << "Error: Could not finish BSON object (check) in lmc::Server::setBasicBoardData!"
              << std::endl;
    return false;
  }
  // build en passant object
  BSON enPassant;
  if (board.enPassant() == Field::none)
  {
    if (!enPassant.appendNull("column") || !enPassant.appendNull("row"))
    {
      std::cerr << "Error: Could not append column and row to BSON object in lmc::Server::setBasicBoardData!"
              << std::endl;
      return false;
    }
  }
  else
  {
    if (!enPassant.append("column", std::string(1, column(board.enPassant()))))
    {
      std::cerr << "Error: Could not append column to BSON object in lmc::Server::setBasicBoardData!"
                << std::endl;
      return false;
    }
    if (!enPassant.append("row", row(board.enPassant())))
    {
      std::cerr << "Error: Could not append row to BSON object in lmc::Server::setBasicBoardData!"
                << std::endl;
      return false;
    }
  } // else
  if (!enPassant.finish())
  {
    std::cerr << "Error: Could not finish BSON object (enPassant) in lmc::Server::setBasicBoardData!"
              << std::endl;
    return false;
  }
  //append all objects to subUpdate
  if (!subUpdate.append("castling", castling))
  {
    std::cerr << "Error: Could not append castling to BSON object in lmc::Server::setBasicBoardData!"
              << std::endl;
    return false;
  }
  if (!subUpdate.append("check", check))
  {
    std::cerr << "Error: Could not append check to BSON object in lmc::Server::setBasicBoardData!"
              << std::endl;
    return false;
  }
  if (!subUpdate.append("enPassant", enPassant))
  {
    std::cerr << "Error: Could not append enPassant to BSON object in lmc::Server::setBasicBoardData!"
              << std::endl;
    return false;
  }
  if (!subUpdate.finish())
  {
    std::cerr << "Error: Could not finish BSON object (subUpdate) in lmc::Server::setBasicBoardData!"
              << std::endl;
    return false;
  }

  BSON update;
  if (!update.append("$set", subUpdate))
  {
    std::cerr << "Error: Could not append document to BSON object in lmc::Server::setBasicBoardData!"
              << std::endl;
    return false;
  }
  if (!update.finish())
  {
    std::cerr << "Error: Could not finish BSON object (update) in lmc::Server::setBasicBoardData!"
              << std::endl;
    return false;
  }

  try
  {
    return conn.update("meteor.boards", selector, update);
  } // try-c
  catch(const std::exception& ex)
  {
    std::cerr << "Error: An exception occurred while updating the basic board information!"
              << std::endl << ex.what() << std::endl;
    return false;
  }
  catch(...)
  {
    std::cerr << "Error: An exception occurred while updating the basic board information!"
              << std::endl;
    return false;
  }
}

bool Server::updateBoardFields(const std::string& id, const Board& board)
{
  for (char col = 'a'; col <= 'h'; ++col)
  {
    for (int r = 1; r <= 8; ++r)
    {
      if (!updateFieldOnBoard(id, board, toField(col, r)))
      {
        std::cerr << "Error while updating field " << std::string(1, col) << r
                  << " of board " << id << "!" << std::endl;
        return false;
      }
    } // for row
  } // for column
  return true;
}

} // namespace

} // namespace

} // namespace

} // namespace
