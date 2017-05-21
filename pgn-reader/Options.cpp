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

#include "Options.hpp"
#include <iostream>
#include "../util/strings.hpp"

namespace simplechess
{

PgnReaderOptions::PgnReaderOptions()
: inputFile(""),
  delayMilliseconds(1000),
  help(false)
{
}

bool PgnReaderOptions::parse(const int argc, char** argv)
{
  if (nullptr == argv)
    return false;
  for (int i = 1; i < argc; ++i)
  {
    if (nullptr == argv[i])
      return false;
    const std::string param = std::string(argv[i]);
    if (param == "--delay")
    {
      if (argc > i + 1)
      {
        const std::string ms = std::string(argv[i+1]);
        int dummy = -1;
        if (!util::stringToInt(ms, dummy))
        {
          std::cout << "Parameter " << param << " must be followed by an integer!\n";
          return false;
        }
        if (dummy < 0)
        {
          std::cout << "The given value for delay is out of range. Is must be a positive number.\n";
          return false;
        }
        delayMilliseconds = dummy;
        //Skip next argument, because that was already processed as delay value.
        ++i;
      }
      else
      {
        std::cout << "There must be a number after " << param << " to specifiy"
                  << " the delay in milliseconds!\n";
        return false;
      }
    } //if delay
    else if ((param == "--pgn") || (param == "--file"))
    {
      if (argc > i + 1)
      {
        inputFile = std::string(argv[i+1]);
        //Skip next argument, because that was already processed as file name.
        ++i;
      }
      else
      {
        std::cout << "There must be a file name after " << param << " to path "
                  << " to the Portable Game Notation file!\n";
        return false;
      }
    }
    else if ((param == "--help") || (param == "-?") || (param == "/?"))
    {
      help = true;
    }
    else
    {
      std::cout << "Error: Invalid parameter \"" << param << "\"!\n";
      return false;
    }
  } //for
  return true;
}

} //namespace
