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

#include <iostream>
#include "io-utils.hpp"
#include "CommandParser.hpp"
#include "Engine.hpp"
#include "../util/GitInfos.hpp"
#include "../util/Version.hpp"

void showVersion()
{
  simplechess::GitInfos info;
  std::cout << "simplechess-engine, " << simplechess::version << "\n"
            << "\n"
            << "Version control commit: " << info.commit() << "\n"
            << "Version control date:   " << info.date() << std::endl;
}

void showHelp()
{
  std::cout << "simplechess-engine [OPTIONS]\n"
            << "\n"
            << "options:\n"
            << "  -? | --help     - shows this help message and exits\n"
            << "  -v | --version  - shows version information and exits\n";
}

int main(int argc, char** argv)
{
  using namespace simplechess;

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
      else
      {
        std::cerr << "Error: Unknown parameter " << param << "!\n"
                  << "Use --help to show available parameters." << std::endl;
        return 1;
      }
    } // for i
  } // if arguments are there

  // No output buffering.
  disableStdoutBuffering();
  // No input buffering.
  disableStdinBuffering();

  while (!Engine::get().quitRequested())
  {
    std::string command;
    std::getline(std::cin, command, '\n');
    CommandParser::parse(command);
    // TODO: separate thread for command processing by engine
    Engine::get().processQueue();
  } // while

  return 0;
}
