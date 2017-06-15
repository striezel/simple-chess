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

#ifndef SIMPLECHESS_DB_MONGO_LMC_SERVER_HPP
#define SIMPLECHESS_DB_MONGO_LMC_SERVER_HPP

#include "../Server.hpp"
#include "Connection.hpp"

namespace simplechess
{

namespace db
{

namespace mongo
{

namespace libmongoclient
{

class Server : public simplechess::db::mongo::Server
{
  public:
    /** \brief connects to a MongoDB server
     *
     * \param hostname  hostname or IP of the MongoDB server
     * \param port      port number for the server
     * \param slaveAcceptable  whether it is acceptable to connect to a slave in a replica set
     */
    Server(const std::string& hostname, const uint16_t port, const bool slaveAcceptable);


    /** \brief destructor - closes the connection to the server (if still open)
     */
    virtual ~Server();


    /** \brief gets a list of board IDs from the server
     *
     * \param boardIds  vector that will be used to store the IDs
     * \return Returns true, if retrieval was successful.
     *         Returns false otherwise.
     */
    virtual bool boardList(std::vector<std::string>& boardIds);


    /** \brief gets a single chess board from the database
     *
     * \param id   the ID of the board
     * \param board   board instance that will be used to store the data
     * \return Returns true, if retrieval was successful.
     *         Returns false, if an error occurred.
     */
    virtual bool getBoard(const std::string& id, Board& board);
  private:
    Connection conn; /**< server connection */
}; //class

} //namespace

} //namespace

} //namespace

} //namespace

#endif // SIMPLECHESS_DB_MONGO_LMC_SERVER_HPP
