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

#include "portable-game-notation.hpp"
#include <stdexcept>
#include "../util/strings.hpp"

namespace simplechess
{

PortableGameNotation::PortableGameNotation()
: mEvent("?"),
  mSite("?"),
  mDateYear(-1),
  mDateMonth(-1),
  mDateDay(-1),
  mRound("?"),
  mWhite("?"),
  mBlack("?"),
  mResult(Result::Unknown),
  mOtherTags(std::map<std::string, std::string>()),
  mMoves(std::map<unsigned int, std::pair<HalfMove, HalfMove>>())
{
}

std::string PortableGameNotation::resultToString(const Result& res)
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

const std::string& PortableGameNotation::event() const
{
  return mEvent;
}

const std::string& PortableGameNotation::site() const
{
  return mSite;
}

std::string PortableGameNotation::date() const
{
  std::string temp;
  if (mDateYear != -1)
    temp += util::intToString(mDateYear);
  else
    temp += "????";
  temp += ".";
  if (mDateMonth != -1)
  {
    if (mDateMonth < 10)
      temp += "0";
    temp += util::intToString(mDateMonth);
  }
  else
    temp += "??";
  temp += ".";
  if (mDateDay != -1)
  {
    if (mDateDay < 10)
      temp += "0";
    temp += util::intToString(mDateDay);
  }
  else
    temp += "??";
  return temp;
}

const std::string& PortableGameNotation::round() const
{
  return mRound;
}

const std::string& PortableGameNotation::white() const
{
  return mWhite;
}

const std::string& PortableGameNotation::black() const
{
  return mBlack;
}

const Result PortableGameNotation::result() const
{
  return mResult;
}

std::string PortableGameNotation::tag(const std::string& tagName) const
{
  const auto iter = mOtherTags.find(tagName);
  if (iter != mOtherTags.end())
    return iter->second;
  //tag from standard tag roster?
  if (tagName == "Event")
    return event();
  if (tagName == "Site")
    return site();
  if (tagName == "Date")
    return date();
  if (tagName == "Round")
    return round();
  if (tagName == "White")
    return white();
  if (tagName == "Black")
    return black();
  if (tagName == "Result")
    return resultToString(result());
  //tag not found
  return std::string();
}

} //namespace
