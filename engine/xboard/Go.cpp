/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2021  Dirk Stolle

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

#include "Go.hpp"
#include "../Engine.hpp"
#include "../io-utils.hpp"

namespace simplechess::xboard
{

bool Go::process()
{
  // TODO: Check whether this implementation does what the protocol
  // specification expects the engine to do.
  auto& eng = Engine::get();
  eng.setForceMode(false);
  eng.timing().opponent().stop();
  eng.timing().self().start();
  eng.move();
  eng.timing().self().stop();
  return true;
}

} // namespace
