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

#include "BSON.hpp"
#include <stdexcept>

namespace simplechess
{

namespace db
{

namespace mongo
{

BSON::BSON()
: mBson(bson_new()),
  mFinished(false)
{
  if (nullptr == mBson)
    throw std::runtime_error("Could not create new BSON instance!");
}

BSON::BSON(bson * b)
: mBson(b),
  mFinished(true)
{
  if (nullptr == mBson)
    throw std::runtime_error("Initial value for BSON is null!");
}

BSON::~BSON()
{
  bson_free(mBson);
}

BSON::BSON(BSON&& other)
{
  mBson = other.mBson;
  mFinished = other.mFinished;
  other.mBson = bson_new();
  other.mFinished = false;
}

bool BSON::append(const std::string& key, const std::string& value)
{
  return bson_append_string(mBson, key.c_str(), value.c_str(), value.size());
}

bool BSON::append(const std::string& key, const bool b)
{
  return bson_append_boolean(mBson, key.c_str(), b);
}

bool BSON::append(const std::string& key, const double dbl)
{
  return bson_append_double(mBson, key.c_str(), dbl);
}

bool BSON::append(const std::string& key, const int32_t i32)
{
  return bson_append_int32(mBson, key.c_str(), i32);
}

bool BSON::append(const std::string& key, const int64_t i64)
{
  return bson_append_int64(mBson, key.c_str(), i64);
}

bool BSON::appendNull(const std::string& key)
{
  return bson_append_null(mBson, key.c_str());
}

bool BSON::finished() const
{
  return mFinished;
}

bool BSON::finish()
{
  if (bson_finish(mBson))
  {
    mFinished = true;
    return true;
  }
  return false;
}

std::vector<std::pair<std::string, std::string>> BSON::keys() const
{
  bson_cursor * cursor = bson_cursor_new(mBson);
  if (nullptr == cursor)
    throw std::runtime_error("Could not get BSON cursor!");
  std::vector<std::pair<std::string, std::string>> result;
  while (bson_cursor_next(cursor))
  {
    result.push_back(std::pair<std::string, std::string>(
        std::string(bson_cursor_key(cursor)),
        std::string(bson_cursor_type_as_string(cursor))));
  } //while
  bson_cursor_free(cursor);
  return result;
}

bson* BSON::raw() const
{
  return mBson;
}

} //namespace

} //namespace

} //namespace
