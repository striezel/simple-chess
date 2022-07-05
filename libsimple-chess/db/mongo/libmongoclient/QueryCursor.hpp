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

#ifndef SIMPLE_CHESS_DB_MONGO_LMC_QUERYCURSOR_HPP
#define SIMPLE_CHESS_DB_MONGO_LMC_QUERYCURSOR_HPP

#include <string>
#include <mongo-client/mongo-sync-cursor.h>
#include "BSON.hpp"

namespace simplechess::db::mongo
{

class QueryCursor
{
  public:
    /** \brief default constructor
     *
     * \param cur the underlying cursor
     * \param packet   the corresponding wire packet (can be nullptr)
     */
    QueryCursor(mongo_sync_cursor * cur, mongo_packet * packet);


    /** destructor */
    ~QueryCursor();


    //delete copy constructor
    QueryCursor(const QueryCursor& other) = delete;

    //delete assignment operator
    QueryCursor& operator=(const QueryCursor& other) = delete;

    //move constructor
    QueryCursor(QueryCursor&& other);


    /** \brief Moves the cursor to the next element.
     *
     * \return Returns true, if the cursor was moved.
     *         Returns false, if the cursor was not moved or an error occurred.
     */
    bool next();


    /** \brief Gets the data at the current cursor position.
     *
     * \return a BSON object that contains the data
     */
    BSON data() const;
  private:
    mongo_sync_cursor * mCursor; /**< low level cursor handle */
    mongo_packet * mPacket; /**< low level packet related to cursor */
}; // class

} // namespace

#endif // SIMPLE_CHESS_DB_MONGO_LMC_QUERYCURSOR_HPP
