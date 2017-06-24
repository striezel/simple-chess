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


    /** \brief updates a single chess board in the database
     *
     * \param id   the ID of the board in the MongoDB
     * \param board   board instance that contains the data that shall be written into the DB
     * \return Returns true, if database update was successful.
     *         Returns false, if an error occurred.
     */
    virtual bool updateBoard(const std::string& id, const Board& board);


    /** \brief updates a single field on a chess board in the database
     *
     * \param id   the ID of the board in the MongoDB
     * \param board   board instance that contains the data that shall be written into the DB
     * \param f       field that shall be updated
     * \return Returns true, if database update was successful.
     *         Returns false, if an error occurred.
     */
    virtual bool updateFieldOnBoard(const std::string& id, const Board& board, const Field f);
  private:
    Connection conn; /**< server connection */


    /** \brief gets basic data like player to move, e.p., castling for a board
     *         from the database
     *
     * \param elem BSON element for the board
     * \param board   Board structure to save the data
     * \return Returns true in case of success.
     *         Returns false, if an error occurred.
     */
    bool getBasicBoardData(const BSON& elem, Board& board);


    /** \brief gets the field data for a board
     *
     * \param id   the ID of the board
     * \param board   board instance that will be used to store the data
     * \return Returns true in case of success.
     *         Returns false, if an error occurred.
     */
    bool getBoardFields(const std::string& id, Board& board);


    /** \brief updates basic data like player to move, e.p., castling for a board
     *         in the database
     *
     * \param id id of the board
     * \param board   Board structure that contains the data to be set
     * \return Returns true in case of success.
     *         Returns false, if an error occurred.
     */
    bool updateBasicBoardData(const std::string& id, const Board& board);


    /** \brief updates the field data for a board in the database
     *
     * \param id   the ID of the board
     * \param board   board instance that contains the data to be set
     * \return Returns true in case of success.
     *         Returns false, if an error occurred.
     * \remarks This method does not check whether a board with the given id
     *          exists. If there is no matching board, the update will still
     *          succeed, despite the fact that no documents have been updated
     *          in that case.
     */
    bool updateBoardFields(const std::string& id, const Board& board);
}; //class

} //namespace

} //namespace

} //namespace

} //namespace

#endif // SIMPLECHESS_DB_MONGO_LMC_SERVER_HPP
