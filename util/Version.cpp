/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2024  Dirk Stolle

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

#include "Version.hpp"
#include <iostream>
#include <iterator>
#include <numeric>

namespace simplechess
{

void license(const std::vector<unsigned int> years)
{
  if (years.empty())
  {
    license({ 2024 });
    return;
  }
  auto comma_fold = [](std::string s, unsigned int i)
  {
     return std::move(s) + ", " + std::to_string(i);
  };
  const auto timeline = std::accumulate(std::next(years.begin()), years.end(),
                            std::to_string(years[0]), comma_fold);
  std::cout << "Copyright (C) " << timeline << "  Dirk Stolle\n"
            << "License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.\n"
            << "This program is free software: you are free to change and redistribute it.\n"
            << "There is NO WARRANTY, to the extent permitted by law.\n";
}

}
