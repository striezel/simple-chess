/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2018, 2024  Dirk Stolle

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
#include "../../util/strings.hpp"

namespace simplechess
{

MeteorChessOptions::MeteorChessOptions()
: boardId(""),
  hostname(""),
  port(0),
  help(false),
  version(false),
  json(false),
  move(false),
  evaluators("")
{
}

bool MeteorChessOptions::parse(const int argc, char** argv)
{
  if (nullptr == argv)
    return false;
  for (int i = 1; i < argc; ++i)
  {
    if (nullptr == argv[i])
      return false;
    const std::string param = std::string(argv[i]);
    // help?
    if ((param == "--help") || (param == "-?") || (param == "/?"))
    {
      help = true;
    }
    // version
    else if ((param == "--version") || (param == "-v") || (param == "/v"))
    {
      version = true;
    }
    // id of board in meteor-chess
    else if ((param == "--board") || (param == "--board-id"))
    {
      if (!boardId.empty())
      {
        std::cerr << "Error: The board ID cannot be specified more than once!\n";
        return false;
      }
      if (argc > i + 1)
      {
        boardId = std::string(argv[i+1]);
        // Skip next argument, because that was already processed as board ID.
        ++i;
      }
      else
      {
        std::cout << "There must be a board ID after " << param << "!\n";
        return false;
      }
    } // board ID
    // hostname of MongoDB
    else if ((param == "--hostname") || (param == "--host"))
    {
      if (!hostname.empty())
      {
        std::cerr << "Error: The host name cannot be specified more than once!\n";
        return false;
      }
      if (argc > i + 1)
      {
        hostname = std::string(argv[i+1]);
        //Skip next argument, because that was already processed as hostname.
        ++i;
      }
      else
      {
        std::cout << "There must be a host name after " << param << "!\n";
        return false;
      }
    } // hostname
    // port of MongoDB
    else if (param == "--port")
    {
      if (argc > i + 1)
      {
        if (port != 0)
        {
          std::cerr << "Error: The port number cannot be specified more than once!\n";
          return false;
        }
        const std::string portString = std::string(argv[i+1]);
        int dummy = -1;
        if (!util::stringToInt(portString, dummy))
        {
          std::cerr << "Parameter " << param << " must be followed by a port number!\n";
          return false;
        }
        if ((dummy <= 0) || (dummy > 32767))
        {
          std::cerr << "The given port number is out of range. It must be in [1;32767].\n";
          return false;
        }
        port = static_cast<uint16_t>(dummy);
        // Skip next argument, because that was already processed as port number.
        ++i;
      }
      else
      {
        std::cerr << "There must be a port number after " << param << "!\n";
        return false;
      }
    } // if port number
    // enable JSON output
    else if (param == "--json")
    {
      if (json)
      {
        std::cerr << "Error: The parameter " << param << " cannot be specified more than once!\n";
        return false;
      }
      json = true;
    } // if JSON
    // perform move, too?
    else if ((param == "--move") || (param == "--perform"))
    {
      if (move)
      {
        std::cerr << "Error: The parameter " << param << " cannot be specified more than once!\n";
        return false;
      }
      move = true;
    } // if perform move
    // custom list of evaluators
    else if ((param == "--evaluators") || (param == "--evaluator") || (param == "-e"))
    {
      if (!evaluators.empty())
      {
        std::cerr << "Error: The parameter " << param << " cannot be specified more than once!\n";
        return false;
      }
      if (argc > i + 1)
      {
        evaluators = std::string(argv[i+1]);
        // Skip next argument, because that was already processed.
        ++i;
      }
      else
      {
        std::cerr << "There must be a list of evaluators after " << param << "!\n";
        return false;
      }
    } // if list of evaluators was given
    else
    {
      std::cerr << "Error: Invalid parameter \"" << param << "\"!\n";
      return false;
    }
  } // for

  // Set default values.
  if (hostname.empty())
  {
    hostname = "localhost";
  }
  if (port == 0)
  {
    port = 3001;
  }
  return true;
}

} // namespace
