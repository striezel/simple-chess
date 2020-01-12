/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2018, 2020  Dirk Stolle

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

#include "CompoundEvaluator.hpp"

namespace simplechess
{

CompoundEvaluator::CompoundEvaluator()
: evaluators(std::vector<std::unique_ptr<Evaluator>>())
{
}

void CompoundEvaluator::add(std::unique_ptr<Evaluator>&& eval)
{
  evaluators.push_back(std::move(eval));
}

int CompoundEvaluator::score(const Board& board) const
{
  int sum = 0;
  for (const auto & evaluator : evaluators)
  {
    sum += evaluator->score(board);
  }
  return sum;
}

std::size_t CompoundEvaluator::size() const noexcept
{
  return evaluators.size();
}

void CompoundEvaluator::clear() noexcept
{
  evaluators.clear();
}

bool CompoundEvaluator::empty() const noexcept
{
  return evaluators.empty();
}

std::string CompoundEvaluator::name() const noexcept
{
  if (empty())
    return "CompoundEvaluator(<empty>)";

  std::string elements;
  for (const auto& elem: evaluators)
  {
    elements.append("," + elem->name());
  }
  elements.erase(0, 1);
  return "CompoundEvaluator(" + elements + ")";
}

} // namespace
