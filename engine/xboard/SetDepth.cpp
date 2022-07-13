/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2021, 2022  Dirk Stolle

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

#include "SetDepth.hpp"
#include "../Engine.hpp"
#ifdef DEBUG
#include "../io-utils.hpp"
#endif // DEBUG

namespace simplechess::xboard
{

SetDepth::SetDepth(const unsigned int depth)
: mDepth(depth)
{
}

bool SetDepth::process()
{
  #ifdef DEBUG
  sendCommand("# depth was " + std::to_string(Engine::get().searchDepth()) + " and got set to " + std::to_string(mDepth) + ".");
  #endif // DEBUG
  Engine::get().setSearchDepth(mDepth);
  return true;
}

} // namespace
