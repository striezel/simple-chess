/*
 -------------------------------------------------------------------------------
    This file is part of the test suite for simple-chess.
    Copyright (C) 2023  Dirk Stolle

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

#include "../../../locate_catch.hpp"
#include "../../../../libsimple-chess/db/mongo/IdGenerator.hpp"

TEST_CASE("IdGenerator::generate")
{
  using namespace simplechess::db::mongo;

  const auto id = IdGenerator::generate();
  REQUIRE_FALSE( id.empty() );

  const auto id2 = IdGenerator::generate();
  REQUIRE_FALSE( id2.empty() );

  REQUIRE( id != id2 );
}

TEST_CASE("IdGenerator::generate with existing ids")
{
  using namespace simplechess::db::mongo;

  SECTION("empty existing ids")
  {
    const auto id = IdGenerator::generate({});
    REQUIRE_FALSE( id.empty() );
  }

  SECTION("some existing ids")
  {
    const std::vector<std::string> existing_ids = {
        "3ztLHcZkWSBSUGdlu",
        "a3cPaNISNhOxxFTge",
        "ZN6ClKJuERVAWn4BL",
        "ChuhjDexe7367OROT"
    };
    const auto generated_id = IdGenerator::generate(existing_ids);
    REQUIRE_FALSE( generated_id.empty() );

    for (const auto& id: existing_ids)
    {
      REQUIRE( id != generated_id );
    }
  }
}
