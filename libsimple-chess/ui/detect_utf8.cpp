/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
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

#include "detect_utf8.hpp"
#include <algorithm>
#include <array>
#include <cstdlib> // for std::getenv()
#include <string>

namespace simplechess::ui
{

std::string getEnvVar(const std::string& name)
{
  const char * value = std::getenv(name.c_str());
  return value != nullptr ? std::string(value) : std::string();
}

bool may_support_utf8()
{
  static const std::array<std::string, 2> variables = {
      "LANG",
      "LC_CTYPE"
  };
  auto contains_utf8 = [](const std::string& name)
  {
    const auto value = getEnvVar(name);
    return value.find("UTF-8") != std::string::npos;
  };

  return std::any_of(variables.begin(), variables.end(), contains_utf8);
}

} // namespace
