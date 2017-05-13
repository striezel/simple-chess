/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016, 2017  Dirk Stolle

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

#include "strings.hpp"
#include <sstream>

namespace simplechess
{

namespace util
{

std::vector<std::string> split(std::string line, const char separator)
{
  std::vector<std::string> result;
  if (line.empty())
  {
    result.push_back("");
    return result;
  }
  std::string::size_type pos = line.find(separator);
  while (pos != std::string::npos)
  {
    result.push_back(line.substr(0, pos));
    line = line.substr(pos+1);
    pos = line.find(separator);
  }//while
  if (!line.empty())
  {
    result.push_back(line);
  }
  return result;
}

std::string intToString(const int value)
{
  std::ostringstream s;
  s << value;
  return s.str();
}

void trimLeft(std::string& str1)
{
  if (str1.empty()) return;
  //trim stuff at begin
  int len = str1.length();
  int pos = 0;
  bool goOn = true;
  while (goOn)
  {
    const char ch = str1.at(pos);
    if ((ch == ' ') or (ch == '\t') || (ch == '\n') || (ch == '\r') || (ch == '\v'))
    {
      ++pos;
      goOn = (pos < len);
    }
    else
    {
      goOn = false;
    }
  }//while
  if (pos >= len)
  {
    str1.clear();
    return;
  }
  else if (pos > 0)
  {
    str1.erase(0, pos);
  }
  return;
}

} //namespace

} //namespace
