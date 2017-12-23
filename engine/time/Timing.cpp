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

#include "Timing.hpp"
#include <algorithm>

namespace simplechess
{

Timing::Timing()
: mMode(TimeControlMode::conventional),
  mSelfClock(Clock(std::chrono::minutes(5))),
  mOpponentClock(Clock(std::chrono::minutes(5))),
  mConventionalMoves(40),
  mConventionalTime(std::chrono::minutes(5)),
  mIncrementalBase(std::chrono::minutes(2)),
  mIncrementalIncrement(std::chrono::seconds(12)),
  mExactSecondsPerMove(std::chrono::seconds(30))
{
}

TimeControlMode Timing::mode() const
{
  return mMode;
}

void Timing::setMode(const TimeControlMode newMode)
{
  mMode = newMode;
}

Clock& Timing::self()
{
  return mSelfClock;
}

Clock& Timing::opponent()
{
  return mOpponentClock;
}

void Timing::setConventional(const int moves, const std::chrono::seconds& time)
{
  // We use std::max() to ensure values of at least one move and one second,
  // because zero or negative values are not useful.
  mConventionalMoves = std::max(moves, 1);
  mConventionalTime = std::max(time, std::chrono::seconds(1));
  if (!mSelfClock.running())
  {
    mSelfClock.reset(mConventionalTime);
  }
  if (!mOpponentClock.running())
  {
    mOpponentClock.reset(mConventionalTime);
  }
}

void Timing::setIncremental(const std::chrono::seconds& base, const std::chrono::seconds& increment)
{
  // We use std::max() to ensure values of at least 10 seconds base time and an
  // increment of at least one second, because zero or negative increment values
  // are not useful, and neither is a base time below ten seconds.
  mIncrementalBase = std::max(base, std::chrono::seconds(10));
  mIncrementalIncrement = std::max(increment, std::chrono::seconds(1));
  if (!mSelfClock.running())
  {
    mSelfClock.reset(base);
  }
  if (!mOpponentClock.running())
  {
    mOpponentClock.reset(base);
  }
}

void Timing::setExact(const std::chrono::seconds& secondsPerMove)
{
  mExactSecondsPerMove = std::max(secondsPerMove, std::chrono::seconds(1));
  if (!mSelfClock.running())
  {
    mSelfClock.reset(mExactSecondsPerMove);
  }
  if (!mOpponentClock.running())
  {
    mOpponentClock.reset(mExactSecondsPerMove);
  }
}

} // namespace
