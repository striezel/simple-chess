/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016, 2017, 2018, 2022  Dirk Stolle

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

#include "Field.hpp"

namespace simplechess
{

Field leftField(const Field f)
{
  if (f == Field::none)
    return Field::none;
  const char col = column(f);
  if (col == 'a')
    return Field::none;
  return toField(static_cast<char>(static_cast<int>(col) - 1), row(f));
}

Field rightField(const Field f)
{
  if (f == Field::none)
    return Field::none;
  const char col = column(f);
  if (col == 'h')
    return Field::none;
  return toField(static_cast<char>(static_cast<int>(col) + 1), row(f));
}

} // namespace
