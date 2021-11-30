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

#include "QueryCursor.hpp"
#include <stdexcept>

namespace simplechess::db::mongo
{

QueryCursor::QueryCursor(mongo_sync_cursor * cur, mongo_packet* packet)
: mCursor(cur),
  mPacket(packet)
{
  if (nullptr == mCursor)
    throw std::runtime_error("MongoDB cursor is null!");
}

QueryCursor::~QueryCursor()
{
  if (mCursor != nullptr)
    mongo_sync_cursor_free(mCursor);
  //if (mPacket != nullptr)
  //  mongo_wire_packet_free(mPacket);
}

QueryCursor::QueryCursor(QueryCursor&& other)
: mCursor(other.mCursor),
  mPacket(other.mPacket)
{
  other.mCursor = nullptr;
  other.mPacket = nullptr;
}

bool QueryCursor::next()
{
  return mongo_sync_cursor_next(mCursor);
}

BSON QueryCursor::data() const
{
  bson* b = mongo_sync_cursor_get_data(mCursor);
  if (nullptr == b)
    throw std::runtime_error("BSON data for current cursor position is null!");
  return std::move(BSON(b));
}

} // namespace
