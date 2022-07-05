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

#ifndef SIMPLE_CHESS_DB_MONGO_LMC_CONNECTION_HPP
#define SIMPLE_CHESS_DB_MONGO_LMC_CONNECTION_HPP

#include <cstdint>
#include <string>
#include <mongo-client/mongo-sync.h>
#include "BSON.hpp"
#include "QueryCursor.hpp"

namespace simplechess::db::mongo
{

class Connection
{
  public:
    /** \brief creates a connection and connects to a MongoDB server
     *
     * \param hostname  hostname or IP of the MongoDB server
     * \param port      port number for the server
     * \param slaveAcceptable  whether it is acceptable to connect to a slave in a replica set
     */
    Connection(const std::string& hostname, const uint16_t port, const bool slaveAcceptable);


    ///deleted copy constructor
    Connection(const Connection& other) = delete;

    ///deleted move constructor
    Connection(Connection&& other) = delete;


    ///deleted assignment operator
    Connection operator=(const Connection& other) = delete;


    /** \brief destructor - disconnects and frees connection handle
     */
    ~Connection();


    /** \brief get the raw connection pointer
     *
     * \return Raw connection pointer.
     */
    mongo_sync_connection * raw() const;


    /** \brief executes a MongoDB query
     *
     * \param ns   database and collection name concatenated, separated with a single dot
     * \param queryB   query BSON object
     * \param limit     maximum limit of results to return (defaults to 1000)
     * \return Returns a query cursor in case of success.
     *         Throws an exception, if the query failed.
     */
    QueryCursor query(const std::string& ns, const BSON& queryB, const unsigned int limit = 100);


    /** \brief insert a document into a MongoDB collection
     *
     * \param ns   database and collection name concatenated, separated with a single dot
     * \param document  document that shall be inserted
     * \return Returns true, if insert succeeded.
     *         Returns false, if an error occurred.
     */
    bool insert(const std::string& ns, const BSON& document);


    /** \brief performs an update in a MongoDB collection
     *
     * \param ns   database and collection name concatenated, separated with a single dot
     * \param selector  query selector
     * \param update    update object
     * \return Returns true, if update succeeded.
     *         Returns false, if an error occurred.
     */
    bool update(const std::string& ns, const BSON& selector, const BSON& update);
  private:
    mongo_sync_connection * conn; /**< MongoDB connection handle */
}; // class

} // namespace

#endif // SIMPLE_CHESS_DB_MONGO_LMC_CONNECTION_HPP
