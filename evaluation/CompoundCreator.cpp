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

#include "CompoundCreator.hpp"
#include <set>
#include "CastlingEvaluator.hpp"
#include "CheckEvaluator.hpp"
#include "LinearMobilityEvaluator.hpp"
#include "MaterialEvaluator.hpp"
#include "PromotionEvaluator.hpp"
#include "RootMobilityEvaluator.hpp"
#include "../util/strings.hpp"

namespace simplechess
{

const std::string CompoundCreator::IdCastling = "castling";
const std::string CompoundCreator::IdCheck = "check";
const std::string CompoundCreator::IdLinearMobility = "linearmobility";
const std::string CompoundCreator::IdMaterial = "material";
const std::string CompoundCreator::IdPromotion = "promotion";
const std::string CompoundCreator::IdRootMobility = "rootmobility";

bool CompoundCreator::create(const std::string& evaluators, CompoundEvaluator& compound)
{
  std::set<std::string> ids;
  const auto parts = util::split(evaluators, ',');
  if (parts.empty())
  {
    std::cout << "Error: List of evaluators is empty!\n";
    return false;
  }
  // Check whether ids are unique and not empty.
  for (const std::string& id : parts)
  {
    if (id.empty())
    {
      std::cout << "Error: Empty ids for evaluators are not allowed!\n";
      return false;
    }
    if (ids.find(id) != ids.end())
    {
      std::cout << "Error: Id " << id << " was given more than once!\n";
      return false;
    }
    ids.insert(id);
  } // for
  // Clear existing evaluators in compound (if any).
  compound.clear();
  // Add new evaluators by id.
  for (const std::string& id : ids)
  {
    if (id == IdCastling)
      compound.add(std::unique_ptr<Evaluator>(new CastlingEvaluator()));
    else if (id == IdCheck)
      compound.add(std::unique_ptr<Evaluator>(new CheckEvaluator()));
    else if (id == IdLinearMobility)
      compound.add(std::unique_ptr<Evaluator>(new LinearMobilityEvaluator()));
    else if (id == IdMaterial)
      compound.add(std::unique_ptr<Evaluator>(new MaterialEvaluator()));
    else if (id == IdPromotion)
      compound.add(std::unique_ptr<Evaluator>(new PromotionEvaluator()));
    else if (id == IdRootMobility)
      compound.add(std::unique_ptr<Evaluator>(new RootMobilityEvaluator()));
    else
    {
      std::cout << "Error: Id \"" << id << "\" does not identify a known evaluator type!\n";
      return false;
    }
  } // for
  // Success - unless compound is empty.
  return !compound.empty();
}

void CompoundCreator::getDefault(CompoundEvaluator& compound)
{
  compound.clear();
  // Add the five evaluators we use by default.
  compound.add(std::unique_ptr<Evaluator>(new MaterialEvaluator()));
  compound.add(std::unique_ptr<Evaluator>(new LinearMobilityEvaluator()));
  compound.add(std::unique_ptr<Evaluator>(new PromotionEvaluator()));
  compound.add(std::unique_ptr<Evaluator>(new CheckEvaluator()));
  compound.add(std::unique_ptr<Evaluator>(new CastlingEvaluator()));
}

} // namespace
