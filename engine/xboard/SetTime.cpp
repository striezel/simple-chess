/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2021, 2022  Dirk Stolle

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

#include "SetTime.hpp"
#include "../Engine.hpp"
#ifdef DEBUG
#include "../io-utils.hpp"
#endif // DEBUG

namespace simplechess::xboard
{

SetTime::SetTime(const int centiseconds, const bool opponent)
: mCentiseconds(centiseconds),
  mOpponent(opponent)
{
}

bool SetTime::process()
{
  Clock& cl = mOpponent ? Engine::get().timing().opponent() : Engine::get().timing().self();
  #ifdef DEBUG
  const auto origCentis = cl.remaining().count();
  sendCommand("# clock time was " + std::to_string(origCentis) + " cs and got set to " + std::to_string(mCentiseconds) + " cs");
  #endif // DEBUG
  cl.setRemaining(centiseconds(mCentiseconds));
  return true;
}

} // namespace
