/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2020  Dirk Stolle

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

#include <iostream>
#include <string>
#include "../util/GitInfos.hpp"
#include "../util/ReturnCodes.hpp"
#include "../util/Version.hpp"
#include "competing.hpp"

void showVersion()
{
  simplechess::GitInfos info;
  std::cout << "simple-chess-competing-evaluators, " << simplechess::version << "\n"
            << "\n"
            << "Version control commit: " << info.commit() << "\n"
            << "Version control date:   " << info.date() << std::endl;
}

void showHelp()
{
  std::cout << "simple-chess-competing-evaluators [OPTIONS]\n"
            << "\n"
            << "options:\n"
            << "  -? | --help     - shows this help message and exits\n"
            << "  -v | --version  - shows version information and exits\n";
}

int main(int argc, char** argv)
{
  if ((argc > 1) && (argv != nullptr))
  {
    for (int i = 1; i < argc; ++i)
    {
      if (argv[i] == nullptr)
      {
        std::cerr << "Error: Parameter at index " << i << " is null pointer!\n";
        return 1;
      }
      const std::string param(argv[i]);
      if ((param == "-v") || (param == "--version"))
      {
        showVersion();
        return 0;
      } // if version
      else if ((param == "-?") || (param == "--help") || (param == "/?"))
      {
        showHelp();
        return 0;
      } // if help
      // Should never happen.
      else
      {
        std::cerr << "Error: Unknown parameter " << param << "!\n"
                  << "Use --help to show available parameters." << std::endl;
        return simplechess::rcInvalidParameter;
      }
    } // for i
  } // if arguments are there

  std::cout << "Pairing all evaluator combinations, this will take quite some time..."
            << std::endl;
  simplechess::Competition::compete(simplechess::Competition::allEvaluators);
  std::cout << "Finished." << std::endl;
  return 0;
}
