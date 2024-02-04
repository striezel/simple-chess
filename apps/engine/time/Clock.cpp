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

#include "Clock.hpp"
#include <algorithm>

namespace simplechess
{

Clock::Clock(const centiseconds& initialTime)
: mInitial(initialTime),
  mRemaining(initialTime),
  mRunning(false),
  mStart(std::chrono::steady_clock::now())
{
}

void Clock::start()
{
  if (!mRunning)
  {
    mRunning = true;
    mStart = std::chrono::steady_clock::now();
  }
}

void Clock::stop()
{
  if (mRunning)
  {
    mRunning = false;
    const auto elapsedT = std::chrono::steady_clock::now() - mStart;
    mRemaining = mRemaining - std::chrono::duration_cast<centiseconds>(elapsedT);
  }
}

bool Clock::running() const
{
  return mRunning;
}

centiseconds Clock::remaining() const
{
  if (running())
  {
    return mRemaining - elapsed();
  }
  else
  {
    return mRemaining;
  }
}

void Clock::setRemaining(const centiseconds& timeLeft)
{
  if (!running())
  {
    mRemaining = timeLeft;
  }
}

centiseconds Clock::elapsed() const
{
  if (running())
  {
    const auto elapsedT = std::chrono::steady_clock::now() - mStart;
    return std::chrono::duration_cast<centiseconds>(elapsedT);
  }
  else
  {
    return centiseconds::zero();
  }
}

void Clock::reset()
{
  mRunning = false;
  mRemaining = mInitial;
}

void Clock::reset(const centiseconds& initialAmount)
{
  mInitial = std::max(centiseconds(1), initialAmount);
  reset();
}

} // namespace
