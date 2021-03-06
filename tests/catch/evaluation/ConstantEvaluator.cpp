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

#include "ConstantEvaluator.hpp"

namespace simplechess
{

ConstantEvaluator::ConstantEvaluator(const int c)
: constantScore(c)
{
}

int ConstantEvaluator::score(const Board& board) const
{
  return constantScore;
}

std::string ConstantEvaluator::name() const noexcept
{
  return "ConstantEvaluator(" + std::to_string(constantScore) + ")";
}

} // namespace
