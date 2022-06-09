/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2022  Dirk Stolle

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

namespace simplechess::pgn
{

UnconsumedTokensException::UnconsumedTokensException(const std::size_t _nextIdx, const std::size_t tokenSize, const std::vector<Token>& leftOverTokens)
: ParserException("Not all tokens have been consumed! Next index is "
      + std::to_string(_nextIdx) + ", but there are "
      + std::to_string(tokenSize) + " tokens in total."),
  nextIdx(_nextIdx),
  totalSize(tokenSize),
  remainingTokens(leftOverTokens)
{
}

std::size_t UnconsumedTokensException::nextIndex() const
{
  return nextIdx;
}

std::size_t UnconsumedTokensException::totalTokenCount() const
{
  return totalSize;
}

const std::vector<Token>& UnconsumedTokensException::unprocessedTokens() const
{
  return remainingTokens;
}

} // namespace
