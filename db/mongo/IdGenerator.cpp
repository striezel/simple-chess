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

#include "IdGenerator.hpp"
#include <algorithm>
#include <random>

namespace simplechess
{

namespace db
{

namespace mongo
{


std::string IdGenerator::generate()
{
  static const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  const std::string::size_type idLength = 17;
  std::random_device randDev;
  std::mt19937 generator(randDev());
  std::uniform_int_distribution<unsigned int> distrib(0, alphabet.size()-1);
  std::string id(idLength, 'a');
  for (std::string::size_type i = 0; i < idLength; ++i)
  {
    id[i] = alphabet[distrib(generator)];
  }
  return id;
}


std::string IdGenerator::generate(const std::vector<std::string>& existingIds)
{
  std::string id = generate();
  while (std::find(existingIds.begin(), existingIds.end(), id) != existingIds.end())
  {
    id = generate();
  }
  return id;
}

} //namespace

} //namespace

} //namespace
