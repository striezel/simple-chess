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
#include <iostream>
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
  mBson = nullptr;
}

BSON& BSON::operator=(const BSON& other)
{
  //avoid self assignment
  if (this == &other)
    return *this;
  //copy
  mBson = bson_new_from_data(bson_data(other.mBson), bson_size(other.mBson));
  //Objects created via bson_new_from_data() are never finished, so they have
  // to be finished manually, if necessary.
  if (other.mFinished)
  {
    if (!bson_finish(mBson))
      throw std::runtime_error("BSON could not be finished!");
  }
  mFinished = other.mFinished;
  return *this;
}

BSON::BSON(BSON&& other)
: mBson(other.mBson),
  mFinished(other.mFinished)
{
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

bool BSON::append(const std::string& key, const std::chrono::milliseconds msSinceEpoch)
{
  return bson_append_utc_datetime(mBson, key.c_str(), msSinceEpoch.count());
}

bool BSON::append(const std::string& key, const BSON& doc)
{
  return bson_append_document(mBson, key.c_str(), doc.mBson);
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

std::string BSON::getTypeOfKey(const std::string& key) const
{
  if (key.empty())
    return std::string();
  bson_cursor* bc = bson_find(mBson, key.c_str());
  if (nullptr == bc)
    return std::string();
  bson_type t =  bson_cursor_type(bc);
  bson_cursor_free(bc);
  bc = nullptr;
  return std::string(bson_type_as_string(t));
}

bool BSON::isNull(const std::string& key) const
{
  if (key.empty())
    return false;
  bson_cursor* bc = bson_find(mBson, key.c_str());
  if (nullptr == bc)
    return false;
  const bool is_null = bson_cursor_type(bc) == BSON_TYPE_NULL;
  bson_cursor_free(bc);
  bc = nullptr;
  return is_null;
}

bool BSON::getString(const std::string& key, std::string& valueOut) const
{
  if (key.empty())
    return false;
  bson_cursor* bc = bson_find(mBson, key.c_str());
  if (nullptr == bc)
    return false;
  const char* str = nullptr;
  const auto success = bson_cursor_get_string(bc, &str);
  if (success)
  {
    valueOut = std::string(str);
  }
  else
  {
    std::cout << "Error: Could not find element with key \"" << key << "\"!" << std::endl;
  }
  bson_cursor_free(bc);
  bc = nullptr;
  return success;
}

bool BSON::getInt32(const std::string& key, int32_t& valueOut) const
{
  if (key.empty())
    return false;
  bson_cursor* bc = bson_find(mBson, key.c_str());
  if (nullptr == bc)
    return false;
  gint32 i32 = 0;
  auto success = bson_cursor_get_int32(bc, &i32);
  if (success)
  {
    valueOut = i32;
  }
  else
  {
    double dbl = 0.0;
    if (bson_cursor_get_double(bc, &dbl))
    {
      const int32_t temp = static_cast<int32_t>(dbl);
      //check that we have an "integer" double and no fractional parts
      if (temp == dbl)
      {
        valueOut = temp;
        success = true;
      }
    } //if get_double succeeded
    if (!success)
    {
      std::cout << "Error: Could not find integer with key \"" << key << "\"!" << std::endl;
    }
  }
  bson_cursor_free(bc);
  bc = nullptr;
  return success;
}

bool BSON::getInt64(const std::string& key, int64_t& valueOut) const
{
  if (key.empty())
    return false;
  bson_cursor* bc = bson_find(mBson, key.c_str());
  if (nullptr == bc)
    return false;
  gint64 i64 = 0;
  const auto success = bson_cursor_get_int64(bc, &i64);
  if (success)
  {
    valueOut = i64;
  }
  else
  {
    std::cout << "Error: Could not find integer with key \"" << key << "\"!" << std::endl;
  }
  bson_cursor_free(bc);
  bc = nullptr;
  return success;
}

bool BSON::getBool(const std::string& key, bool& valueOut) const
{
  if (key.empty())
    return false;
  bson_cursor* bc = bson_find(mBson, key.c_str());
  if (nullptr == bc)
    return false;
  gboolean b = 0;
  const auto success = bson_cursor_get_boolean(bc, &b);
  if (success)
  {
    valueOut = b;
  }
  else
  {
    std::cout << "Error: Could not find boolean with key \"" << key << "\"!" << std::endl;
  }
  bson_cursor_free(bc);
  bc = nullptr;
  return success;
}

bool BSON::getObject(const std::string& key, BSON& valueOut) const
{
  if (key.empty())
    return false;
  bson_cursor* bc = bson_find(mBson, key.c_str());
  if (nullptr == bc)
    return false;
  bson* object = nullptr;
  const auto success = bson_cursor_get_document(bc, &object);
  if (success)
  {
    valueOut = BSON(object);
  }
  else
  {
    std::cout << "Error: Could not find object with key \"" << key << "\"!" << std::endl;
  }
  bson_cursor_free(bc);
  bc = nullptr;
  object = nullptr; //Don't free object, BSON class takes care of it.
  return success;
}

bson* BSON::raw() const
{
  return mBson;
}

} //namespace

} //namespace

} //namespace
