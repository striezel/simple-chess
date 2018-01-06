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

#include "UnconsumedTokensException.hpp"
#include "../util/strings.hpp"

namespace simplechess
{

namespace pgn
{

UnconsumedTokensException::UnconsumedTokensException(const unsigned int _nextIdx, const unsigned int tokenSize, const std::vector<Token>& leftOverTokens)
: ParserException("Not all tokens have been consumed! Next index is "
      + util::intToString(_nextIdx) + ", but there are "
      + util::intToString(tokenSize) + " tokens in total."),
  nextIdx(_nextIdx),
  totalSize(tokenSize),
  remainingTokens(leftOverTokens)
{
}

unsigned int UnconsumedTokensException::nextIndex() const
{
  return nextIdx;
}

unsigned int UnconsumedTokensException::totalTokenCount() const
{
  return totalSize;
}

const std::vector<Token>& UnconsumedTokensException::unprocessedTokens() const
{
  return remainingTokens;
}

} // namespace

} // namespace
