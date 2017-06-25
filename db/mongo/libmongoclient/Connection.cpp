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

#include "Connection.hpp"
#include <cerrno>
#include <stdexcept>
#include "../../../util/strings.hpp"

namespace simplechess
{

namespace db
{

namespace mongo
{

Connection::Connection(const std::string& hostname, const uint16_t port, const bool slaveAcceptable)
: conn(mongo_sync_connect(hostname.c_str(), port, slaveAcceptable))
{
  if (nullptr == conn)
  {
    throw std::runtime_error(std::string("Could not establish connection to MongoDB on ")
              + hostname + ":" + util::intToString(port) + "! Errno: "
              + util::intToString(errno) + ".");
  }
  //enable automatic reconnection to MongoDB
  if (!mongo_sync_conn_set_auto_reconnect(conn, TRUE))
  {
    throw std::runtime_error("Could not enable auto-reconnect in MongoDB connection to "
              + hostname + ":" + util::intToString(port) + "!");
  }
}

Connection::~Connection()
{
  mongo_sync_disconnect(conn);
  conn = nullptr;
}

mongo_sync_connection * Connection::raw() const
{
  return conn;
}

QueryCursor Connection::query(const std::string& ns, const BSON& queryB, const unsigned int limit)
{
  mongo_packet* packet = mongo_sync_cmd_query(conn, ns.c_str(), 0, 0, limit, queryB.raw(), NULL);
  if (nullptr == packet)
    throw std::runtime_error("Could not perform MongoDB query!");
  mongo_sync_cursor* lowLevelCursor = mongo_sync_cursor_new(conn, ns.c_str(), packet);
  if (nullptr == lowLevelCursor)
    throw std::runtime_error("Could not create query cursor from MongoDB query packet!");
  return QueryCursor(lowLevelCursor, packet);
}

bool Connection::insert(const std::string& ns, const BSON& document)
{
  return mongo_sync_cmd_insert(conn, ns.c_str(), document.raw(), nullptr);
}

bool Connection::update(const std::string& ns, const BSON& selector, const BSON& update)
{
  return mongo_sync_cmd_update(conn, ns.c_str(), 0, selector.raw(), update.raw());
}

} //namespace

} //namespace

} //namespace
