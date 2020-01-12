/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2020  Dirk Stolle

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

#include "CheckEvaluator.hpp"
#include "MaterialEvaluator.hpp"
#include "../rules/check.hpp"

namespace simplechess
{

const int CheckEvaluator::defaultCheckValue = 50;
const int CheckEvaluator::defaultCheckmateValue = 2 * MaterialEvaluator::pieceValue(PieceType::king);

CheckEvaluator::CheckEvaluator(const int checkValue, const int checkmateValue)
: mCheckValue(checkValue),
  mCheckmateValue(checkmateValue)
{
}

int CheckEvaluator::score(const Board& board) const
{
  int result = 0;
  if (board.isInCheck(Colour::white))
    result -= mCheckValue;
  if (isCheckMate(board, Colour::white))
    result -= mCheckmateValue;
  if (board.isInCheck(Colour::black))
    result += mCheckValue;
  if (isCheckMate(board, Colour::black))
    result += mCheckmateValue;

  return result;
}

std::string CheckEvaluator::name() const noexcept
{
  return "CheckEvaluator(" + std::to_string(mCheckValue) + ","
    + std::to_string(mCheckmateValue) + ")";
}

} // namespace
