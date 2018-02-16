/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2018  Dirk Stolle

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

#include "CastlingEvaluator.hpp"

namespace simplechess
{

const int CastlingEvaluator::defaultCastlingValue = 100;

CastlingEvaluator::CastlingEvaluator(const int castlingValue)
: mCastlingValue(castlingValue)
{
}

int CastlingEvaluator::score(const Board& board) const
{
  int total = 0;
  const auto& c = board.castling();
  // Check whether white player forfeited the castling opportunity.
  if (!c.white_kingside && !c.white_queenside && (c.white_castled == Ternary::false_value))
    total -= mCastlingValue;
  // Check whether white player forfeited the castling opportunity.
  if (!c.black_kingside && !c.black_queenside && (c.black_castled == Ternary::false_value))
    total += mCastlingValue;
  return total;
}

} // namespace
