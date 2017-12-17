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

#include "Result.hpp"
#include <stdexcept>

namespace simplechess
{

std::string resultToString(const Result& res)
{
  switch(res)
  {
    case Result::Unknown:
         return "*";
    case Result::WhiteWins:
         return "1-0";
    case Result::BlackWins:
         return "0-1";
    case Result::Draw:
         return "1/2-1/2";
    default:
         throw std::invalid_argument("Invalid result type in resultToString()!");
  } //switch
}

Result stringToResult(const std::string& res)
{
  if (res == "1-0")
    return Result::WhiteWins;
  else if (res == "0-1")
    return Result::BlackWins;
  else if (res == "1/2-1/2")
    return Result::Draw;
  else
    return Result::Unknown;
}

} // namespace
