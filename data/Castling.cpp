/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2016, 2018  Dirk Stolle

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

#include "Castling.hpp"

namespace simplechess
{

Castling::Castling()
: white_kingside(true),
  white_queenside(true),
  black_kingside(true),
  black_queenside(true)
{
}

std::string Castling::toFEN() const
{
  std::string result;
  if (white_kingside)
    result.append("K");
  if (white_queenside)
    result.append("Q");
  if (black_kingside)
    result.append("k");
  if (black_queenside)
    result.append("q");
  if (result.empty())
    result = "-";
  return result;
}

void Castling::fromFEN(const std::string& FEN)
{
  white_kingside = (FEN.find('K') != std::string::npos);
  white_queenside = (FEN.find('Q') != std::string::npos);
  black_kingside = (FEN.find('k') != std::string::npos);
  black_queenside = (FEN.find('q') != std::string::npos);
}

} // namespace
