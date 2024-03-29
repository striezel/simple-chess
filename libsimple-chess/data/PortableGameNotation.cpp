/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2018  Dirk Stolle

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

#include "PortableGameNotation.hpp"
#include <stdexcept>
#include "../../util/strings.hpp"

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
  mOtherTags(std::unordered_map<std::string, std::string>()),
  mMoves(std::map<unsigned int, std::pair<HalfMove, HalfMove>>())
{
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
    temp += std::to_string(mDateYear);
  else
    temp += "????";
  temp += ".";
  if (mDateMonth != -1)
  {
    if (mDateMonth < 10)
      temp += "0";
    temp += std::to_string(mDateMonth);
  }
  else
    temp += "??";
  temp += ".";
  if (mDateDay != -1)
  {
    if (mDateDay < 10)
      temp += "0";
    temp += std::to_string(mDateDay);
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

const Result& PortableGameNotation::result() const
{
  return mResult;
}

std::string PortableGameNotation::tag(const std::string& tagName) const
{
  const auto iter = mOtherTags.find(tagName);
  if (iter != mOtherTags.end())
    return iter->second;
  // Is it a tag from the standard tag roster?
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
  // Tag was not found.
  return std::string();
}

void PortableGameNotation::setTag(const std::string& tagName, const std::string& content)
{
  // Is it a tag from standard tag roster?
  if (tagName == "Event")
    mEvent = content;
  else if (tagName == "Site")
    mSite = content;
  else if (tagName == "Date")
  {
    parseDate(content);
  }
  else if (tagName == "Round")
    mRound = content;
  else if (tagName == "White")
    mWhite = content;
  else if (tagName == "Black")
    mBlack = content;
  else if (tagName == "Result")
  {
    mResult = stringToResult(content);
  } // else (Result)
  else
  {
    mOtherTags[tagName] = content;
  }
}

void PortableGameNotation::clearTag(const std::string& tagName)
{
  // Is it a tag from standard tag roster?
  if (tagName == "Event")
    mEvent = "?";
  else if (tagName == "Site")
    mSite = "?";
  else if (tagName == "Date")
  {
    mDateYear = -1;
    mDateMonth = -1;
    mDateDay = -1;
  }
  else if (tagName == "Round")
    mRound = "?";
  else if (tagName == "White")
    mWhite = "?";
  else if (tagName == "Black")
    mBlack = "?";
  else if (tagName == "Result")
  {
    mResult = Result::Unknown;
  }
  else
  {
    mOtherTags.erase(tagName);
  }
}

bool PortableGameNotation::parseDate(const std::string& dateText)
{
  const auto parts = util::split(dateText, '.');
  if (parts.size() != 3)
    return false;
  if ((parts[0].length() != 4) || (parts[1].length() != 2) || (parts[2].length() != 2))
    return false;
  int dummy = -1;
  if (parts[0] == "????")
    mDateYear = -1;
  else if (!util::stringToInt(parts[0], dummy) || (dummy < 1000))
    return false;
  else
    mDateYear = dummy;
  if (parts[1] == "??")
    mDateMonth = -1;
  else if (!util::stringToInt(parts[1], dummy) || (dummy < 1) || (dummy > 12))
    return false;
  else
    mDateMonth = dummy;
  if (parts[2] == "??")
    mDateDay = -1;
  else if (!util::stringToInt(parts[2], dummy) || (dummy < 1) || (dummy > 31))
    return false;
  else
    mDateDay = dummy;
  return true;
}

bool PortableGameNotation::hasMove(const unsigned int moveNumber) const
{
  return mMoves.find(moveNumber) != mMoves.end();
}

unsigned int PortableGameNotation::firstMoveNumber() const
{
  if (!mMoves.empty())
    return mMoves.cbegin()->first;
  return 0;
}

unsigned int PortableGameNotation::lastMoveNumber() const
{
  if (!mMoves.empty())
    return mMoves.crbegin()->first;
  return 0;
}

std::pair<HalfMove, HalfMove> PortableGameNotation::move(const unsigned int moveNumber) const
{
  const auto iter = mMoves.find(moveNumber);
  if (iter != mMoves.end())
    return iter->second;
  // not found, return empty move
  return std::pair<HalfMove, HalfMove>(HalfMove(), HalfMove());
}

void PortableGameNotation::setMove(const unsigned int moveNumber, const HalfMove& whiteMove, const HalfMove& blackMove)
{
  setMove(moveNumber, std::pair<HalfMove, HalfMove>(whiteMove, blackMove));
}

void PortableGameNotation::setMove(const unsigned int moveNumber, const std::pair<HalfMove, HalfMove>& data)
{
  if (moveNumber == 0)
    return;
  mMoves[moveNumber] = data;
}

std::string PortableGameNotation::toString() const
{
  std::string pgn;
  // seven tag roster
  pgn = "[Event \"" + event() + "\"]\n"
      + "[Site \"" + site() + "\"]\n"
      + "[Date \"" + date() + "\"]\n"
      + "[Round \"" + round() + "\"]\n"
      + "[White \"" + white() + "\"]\n"
      + "[Black \"" + black() + "\"]\n"
      + "[Result \"" + resultToString(result()) + "\"]\n";
  for(const auto& item : mOtherTags)
  {
    pgn += "[" + item.first + " \"" + item.second + "\"]\n";
  } // for
  pgn += "\n";
  unsigned int moves = 0;
  for(const auto& mv : mMoves)
  {
    pgn += std::to_string(mv.first) + ". " + mv.second.first.toPGN();
    if (!mv.second.second.empty())
      pgn += " " + mv.second.second.toPGN();
    ++moves;
    // Add line break after four moves.
    if (moves % 4 == 0)
      pgn += "\n";
    // Otherwise add a space character after the move.
    else
      pgn += " ";
  } // for
  if (result() != Result::Unknown)
    pgn += " " + resultToString(result());
  return pgn;
}

} // namespace
