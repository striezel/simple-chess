/*
 -------------------------------------------------------------------------------
    This file is part of the test suite for simple-chess.
    Copyright (C) 2018, 2024  Dirk Stolle

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


#include "../../locate_catch.hpp"
#include "../../../libsimple-chess/evaluation/CompoundCreator.hpp"
#include "../../../libsimple-chess/evaluation/MaterialEvaluator.hpp"
#include "../../../libsimple-chess/evaluation/LinearMobilityEvaluator.hpp"
#include "../../../libsimple-chess/evaluation/PromotionEvaluator.hpp"

TEST_CASE("CompoundCreator")
{
  using namespace simplechess;

  SECTION("create() with empty string shall fail")
  {
    CompoundEvaluator compound;
    REQUIRE_FALSE( CompoundCreator::create("", compound) );
  }

  SECTION("create() with empty parts shall fail")
  {
    CompoundEvaluator compound;
    REQUIRE_FALSE( CompoundCreator::create(",,,,", compound) );
  }

  SECTION("create() with empty unknown ID shall fail")
  {
    CompoundEvaluator compound;
    REQUIRE_FALSE( CompoundCreator::create("foo,bar,baz", compound) );
  }

  SECTION("create() with known single ID succeeds")
  {
    CompoundEvaluator compound;
    REQUIRE( CompoundCreator::create(CompoundCreator::IdMaterial, compound) );
    REQUIRE_FALSE( compound.empty() );
    REQUIRE( compound.size() == 1 );
  }

  SECTION("create() with several known IDs succeeds")
  {
    const std::string evaluators = CompoundCreator::IdMaterial + "," + CompoundCreator::IdCheck + "," + CompoundCreator::IdPromotion;
    CompoundEvaluator compound;
    REQUIRE( CompoundCreator::create(evaluators, compound) );
    REQUIRE_FALSE( compound.empty() );
    REQUIRE( compound.size() == 3 );
  }

  SECTION("create() with duplicate known IDs fails")
  {
    const std::string evaluators = CompoundCreator::IdMaterial + "," + CompoundCreator::IdCheck + "," + CompoundCreator::IdMaterial;
    CompoundEvaluator compound;
    REQUIRE_FALSE( CompoundCreator::create(evaluators, compound) );
  }

  SECTION("support for all known evaluator IDs")
  {
    CompoundEvaluator compound;
    const auto ids = {
        CompoundCreator::IdCastling,
        CompoundCreator::IdCheck,
        CompoundCreator::IdLinearMobility,
        CompoundCreator::IdMaterial,
        CompoundCreator::IdPromotion,
        CompoundCreator::IdRootMobility
    };

    for (const std::string& id : ids)
    {
      compound.clear();
      REQUIRE( CompoundCreator::create(id, compound) );
      REQUIRE_FALSE( compound.empty() );
      REQUIRE( compound.size() == 1 );
    } // for
  }


  SECTION("id sanity checks")
  {
    REQUIRE_FALSE( CompoundCreator::IdCastling.empty() );
    REQUIRE_FALSE( CompoundCreator::IdCheck.empty() );
    REQUIRE_FALSE( CompoundCreator::IdLinearMobility.empty() );
    REQUIRE_FALSE( CompoundCreator::IdMaterial.empty() );
    REQUIRE_FALSE( CompoundCreator::IdPromotion.empty() );
    REQUIRE_FALSE( CompoundCreator::IdRootMobility.empty() );

    // All ids shall be different from each other, i.e. ids are unique.
    REQUIRE_FALSE( CompoundCreator::IdCastling == CompoundCreator::IdCheck );
    REQUIRE_FALSE( CompoundCreator::IdCastling == CompoundCreator::IdLinearMobility );
    REQUIRE_FALSE( CompoundCreator::IdCastling == CompoundCreator::IdMaterial );
    REQUIRE_FALSE( CompoundCreator::IdCastling == CompoundCreator::IdPromotion );
    REQUIRE_FALSE( CompoundCreator::IdCastling == CompoundCreator::IdRootMobility );

    REQUIRE_FALSE( CompoundCreator::IdCheck == CompoundCreator::IdLinearMobility );
    REQUIRE_FALSE( CompoundCreator::IdCheck == CompoundCreator::IdMaterial );
    REQUIRE_FALSE( CompoundCreator::IdCheck == CompoundCreator::IdPromotion );
    REQUIRE_FALSE( CompoundCreator::IdCheck == CompoundCreator::IdRootMobility );

    REQUIRE_FALSE( CompoundCreator::IdLinearMobility == CompoundCreator::IdMaterial );
    REQUIRE_FALSE( CompoundCreator::IdLinearMobility == CompoundCreator::IdPromotion );
    REQUIRE_FALSE( CompoundCreator::IdLinearMobility == CompoundCreator::IdRootMobility );

    REQUIRE_FALSE( CompoundCreator::IdMaterial == CompoundCreator::IdPromotion );
    REQUIRE_FALSE( CompoundCreator::IdMaterial == CompoundCreator::IdRootMobility );

    REQUIRE_FALSE( CompoundCreator::IdPromotion == CompoundCreator::IdRootMobility );
  }

  SECTION("default compound evaluator")
  {
    CompoundEvaluator compound;
    CompoundCreator::getDefault(compound);

    // Compound evaluator shall not be empty.
    REQUIRE_FALSE( compound.empty() );
    // Number of evaluators should be five.
    const auto size = compound.size();
    REQUIRE( size == 5 );
    // Getting default compound again should not change size.
    CompoundCreator::getDefault(compound);
    REQUIRE( size == compound.size() );
  }
}
