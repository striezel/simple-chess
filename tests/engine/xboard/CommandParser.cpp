/*
 -------------------------------------------------------------------------------
    This file is part of the test suite for simple-chess.
    Copyright (C) 2022  Dirk Stolle

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

#include <type_traits>
#include "../../locate_catch.hpp"
#include "../../../engine/Engine.hpp"
#include "../../../engine/xboard/CommandParser.hpp"
#include "../../../engine/xboard/Draw.hpp"
#include "../../../engine/xboard/Error.hpp"
#include "../../../engine/xboard/Force.hpp"
#include "../../../engine/xboard/Go.hpp"
#include "../../../engine/xboard/New.hpp"
#include "../../../engine/xboard/Ping.hpp"
#include "../../../engine/xboard/ProtocolVersion.hpp"
#include "../../../engine/xboard/Quit.hpp"
#include "../../../engine/xboard/ResultCmd.hpp"
#include "../../../engine/xboard/SetDepth.hpp"
#include "../../../engine/xboard/SetTime.hpp"
#include "../../../engine/xboard/Xboard.hpp"

bool noErrorInQueue()
{
  using namespace simplechess;

  const auto& queue = Engine::get().queue();
  for (const auto& ptr: queue)
  {
    const auto error_ptr = dynamic_cast<xboard::Error*>(ptr.get());
    if (error_ptr != nullptr)
      return false;
  }

  return true;
}

template<typename Cmd>
bool lastQueueElementIs()
{
  static_assert( std::is_base_of_v<simplechess::Command, Cmd> );

  const auto& queue = simplechess::Engine::get().queue();
  if (queue.empty())
    return false;
  const auto cmd_ptr = dynamic_cast<Cmd*>(queue.back().get());
  return cmd_ptr != nullptr;
}

void clearCommandQueue()
{
  auto& engine = simplechess::Engine::get();
  engine.mutableQueue().clear();
}

TEST_CASE("CommandParser")
{
  using namespace simplechess::xboard;

  SECTION("empty command string is not an error")
  {
    CommandParser::parse("");
    REQUIRE( noErrorInQueue() );
  }

  SECTION("accepted")
  {
    CommandParser::parse("accepted SomeFeature");
    REQUIRE( noErrorInQueue() );
    // No-op, i. e. no command is generated.
  }


  SECTION("computer")
  {
    CommandParser::parse("computer");
    REQUIRE( noErrorInQueue() );
    // No-op, i. e. no command is generated.
  }

  SECTION("draw")
  {
    CommandParser::parse("draw");
    REQUIRE( noErrorInQueue() );
    REQUIRE( lastQueueElementIs<Draw>() );
  }

  SECTION("force")
  {
    CommandParser::parse("force");
    REQUIRE( noErrorInQueue() );
    REQUIRE( lastQueueElementIs<Force>() );
  }

  SECTION("go")
  {
    CommandParser::parse("go");
    REQUIRE( noErrorInQueue() );
    REQUIRE( lastQueueElementIs<Go>() );
  }

  SECTION("hard")
  {
    CommandParser::parse("hard");
    REQUIRE( noErrorInQueue() );
    // No-op, i. e. no command is generated.
  }

  SECTION("new")
  {
    CommandParser::parse("new");
    REQUIRE( noErrorInQueue() );
    REQUIRE( lastQueueElementIs<New>() );
  }

  SECTION("nopost")
  {
    CommandParser::parse("nopost");
    REQUIRE( noErrorInQueue() );
    // No-op, i. e. no command is generated.
  }

  SECTION("otim")
  {
    SECTION("correct usage with argument")
    {
      CommandParser::parse("otim 2500");
      REQUIRE( noErrorInQueue() );
      REQUIRE( lastQueueElementIs<SetTime>() );
    }

    SECTION("wrong usage with non-integer argument")
    {
      CommandParser::parse("otim blob");
      REQUIRE_FALSE( noErrorInQueue() );
      REQUIRE( lastQueueElementIs<Error>() );
      clearCommandQueue();
    }
  }

  SECTION("ping")
  {
    SECTION("correct usage with argument")
    {
      CommandParser::parse("ping Hello there!");
      REQUIRE( noErrorInQueue() );
      REQUIRE( lastQueueElementIs<Ping>() );
    }

    SECTION("wrong usage without argument")
    {
      CommandParser::parse("ping");
      REQUIRE_FALSE( noErrorInQueue() );
      REQUIRE( lastQueueElementIs<Error>() );
      clearCommandQueue();
    }
  }

  SECTION("post")
  {
    CommandParser::parse("post");
    REQUIRE( noErrorInQueue() );
    // No-op, i. e. no command is generated.
  }

  SECTION("protover")
  {
    CommandParser::parse("protover 2");
    REQUIRE( noErrorInQueue() );
    REQUIRE( lastQueueElementIs<ProtocolVersion>() );
  }

  SECTION("quit")
  {
    CommandParser::parse("quit");
    REQUIRE( noErrorInQueue() );
    REQUIRE( lastQueueElementIs<Quit>() );
  }

  SECTION("random")
  {
    CommandParser::parse("random");
    REQUIRE( noErrorInQueue() );
    // No-op, i. e. no command is generated.
  }

  SECTION("result")
  {
    SECTION("white wins")
    {
      CommandParser::parse("result 1-0");
      REQUIRE( noErrorInQueue() );
      REQUIRE( lastQueueElementIs<ResultCmd>() );
    }

    SECTION("black wins")
    {
      CommandParser::parse("result 0-1");
      REQUIRE( noErrorInQueue() );
      REQUIRE( lastQueueElementIs<ResultCmd>() );
    }

    SECTION("draw")
    {
      CommandParser::parse("result 1/2-1/2");
      REQUIRE( noErrorInQueue() );
      REQUIRE( lastQueueElementIs<ResultCmd>() );
    }

    SECTION("unfinished game")
    {
      CommandParser::parse("result *");
      REQUIRE( noErrorInQueue() );
      REQUIRE( lastQueueElementIs<ResultCmd>() );
    }

    SECTION("result with additional comment")
    {
      clearCommandQueue();
      CommandParser::parse("result * {game not finished because players got hungry and went for dinner}");
      REQUIRE( noErrorInQueue() );
      REQUIRE( lastQueueElementIs<ResultCmd>() );
    }
  }

  SECTION("sd")
  {
    SECTION("correct usage with argument")
    {
      CommandParser::parse("sd 30");
      REQUIRE( noErrorInQueue() );
      REQUIRE( lastQueueElementIs<SetDepth>() );
    }

    SECTION("wrong usage with non-integer argument")
    {
      CommandParser::parse("sd blob");
      REQUIRE_FALSE( noErrorInQueue() );
      REQUIRE( lastQueueElementIs<Error>() );
      clearCommandQueue();
    }

    SECTION("integer argument out of range")
    {
      CommandParser::parse("sd 5000");
      REQUIRE_FALSE( noErrorInQueue() );
      REQUIRE( lastQueueElementIs<Error>() );
      clearCommandQueue();

      CommandParser::parse("sd 0");
      REQUIRE_FALSE( noErrorInQueue() );
      REQUIRE( lastQueueElementIs<Error>() );
      clearCommandQueue();

      CommandParser::parse("sd -1");
      REQUIRE_FALSE( noErrorInQueue() );
      REQUIRE( lastQueueElementIs<Error>() );
      clearCommandQueue();
    }
  }

  SECTION("time")
  {
    SECTION("correct usage with argument")
    {
      CommandParser::parse("time 2500");
      REQUIRE( noErrorInQueue() );
      REQUIRE( lastQueueElementIs<SetTime>() );
    }

    SECTION("wrong usage with non-integer argument")
    {
      CommandParser::parse("time blob");
      REQUIRE_FALSE( noErrorInQueue() );
      REQUIRE( lastQueueElementIs<Error>() );
      clearCommandQueue();
    }
  }

  SECTION("xboard")
  {
    CommandParser::parse("xboard");
    REQUIRE( noErrorInQueue() );
    REQUIRE( lastQueueElementIs<Xboard>() );
  }

  SECTION("some unknown command")
  {
    CommandParser::parse("wurgarblargh");
    REQUIRE_FALSE( noErrorInQueue() );
    REQUIRE( lastQueueElementIs<Error>() );
    clearCommandQueue();
  }
}
