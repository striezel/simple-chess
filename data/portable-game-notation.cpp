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

namespace simplechess
{

PortableGameNotation::PortableGameNotation()
: mEvent("?"),
  mSite("?"),
  mDateYear(-1),
  mDateMonth(-1),
  mDateDay(-1),
  mRound(-1),
  mWhite("?"),
  mBlack("?"),
  mResult(Result::Unknown),
  mOtherTags(std::map<std::string, std::string>()),
  mMoves(std::map<unsigned int, std::pair<HalfMove, HalfMove> >())
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
         throw std::exception("Invalid result type!");
  } //switch
}

} //namespace
