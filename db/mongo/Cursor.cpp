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

#include "Cursor.hpp"
#include <stdexcept>

namespace simplechess
{

namespace db
{

namespace mongo
{

Cursor::Cursor(mongo_sync_cursor * cur)
: mCursor(cur)
{
  if (nullptr == mCursor)
    throw std::runtime_error("MongoDB cursor is null!");
}

Cursor::~Cursor()
{
  mongo_sync_cursor_free(mCursor);
}

bool Cursor::next()
{
  return mongo_sync_cursor_next(mCursor);
}

BSON Cursor::data() const
{
  bson* b = mongo_sync_cursor_get_data(mCursor);
  if (nullptr == b)
    throw std::runtime_error("BSON data for current cursor position is null!");
  return std::move(BSON(b));
}

} //namespace

} //namespace

} //namespace
