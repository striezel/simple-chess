/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2018, 2021, 2024  Dirk Stolle

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
#include "uci/CommandParser.hpp"
#include "xboard/CommandParser.hpp"
#include "Engine.hpp"
#include "ParseLoop.hpp"
#include "../../libsimple-chess/evaluation/CompoundCreator.hpp"
#include "../../util/GitInfos.hpp"
#include "../../util/ReturnCodes.hpp"
#include "../../util/Version.hpp"

void showVersion()
{
  simplechess::GitInfos info;
  std::cout << "simple-chess-engine, " << simplechess::version << "\n"
            << "\n"
            << "Version control commit: " << info.commit() << "\n"
            << "Version control date:   " << info.date() << "\n\n";
  simplechess::license({ 2017, 2018, 2019, 2020, 2021, 2022, 2024 });
}

void showHelp()
{
  std::cout << "simple-chess-engine [OPTIONS]\n"
            << "\n"
            << "Supported program options:\n"
            << "  --help | -?      - Shows this help message and exits.\n"
            << "  --version | -v   - Shows version information and exits.\n"
            << "  --evaluator EVAL - Sets a custom set of evaluators to use where EVAL is a\n"
            << "                     comma-separated list of evaluator ids. Valid ids are:\n"
            << "                       material: evaluator using material value of pieces\n"
            << "                       check: evaluator with bonus for checking opponent\n"
            << "                       castling: evaluator with malus for not castling before\n"
            << "                                 the possibility for castling is lost\n"
            << "                       promotion: evaluator with bonus for pawns that can be\n"
            << "                                  promoted during the next move\n"
            << "                       linearmobility: bonus for number of possible moves over\n"
            << "                                       all pieces by a player\n"
            << "                       rootmobility: like linearmobility, but with a slower\n"
            << "                                     increase for higher move numbers\n"
            << "                     A possible use of this option can look like this:\n"
            << "                       --evaluator check,promotion,material\n"
            << "                     If no evaluator option is given, the program uses a preset.\n"
            << "\n"
            << "simple-chess-engine is an XBoard-compatible chess engine that supports most of\n"
            << "the XBoard commands from protocol version 2. The program expects commands from\n"
            << "XBoard on its standard input and prints responses to the standard output.\n"
            << "For the XBoard protocol see\n"
            << "  <https://www.gnu.org/software/xboard/engine-intf.html>.\n"
            << "\n"
            << "simple-chess-engine also has incomplete UCI protocol support. The program\n"
            << "expects commands from the UCI-compatible GUI on its standard input and prints\n"
            << "responses to the standard output.\n"
            << "For the UCI protocol specification see\n"
            << "  <http://wbec-ridderkerk.nl/html/UCIProtocol.html>.\n";
}

int main(int argc, char** argv)
{
  using namespace simplechess;

  std::string evaluators;

  if ((argc > 1) && (argv != nullptr))
  {
    for (int i = 1; i < argc; ++i)
    {
      if (argv[i] == nullptr)
      {
        std::cerr << "Error: Parameter at index " << i << " is null pointer!\n";
        return rcInvalidParameter;
      }
      const std::string param(argv[i]);
      // version information
      if ((param == "-v") || (param == "--version"))
      {
        showVersion();
        return 0;
      }
      // show help
      else if ((param == "-?") || (param == "--help") || (param == "/?"))
      {
        showHelp();
        return 0;
      }
      // custom list of evaluators
      else if ((param == "--evaluators") || (param == "--evaluator") || (param == "-e"))
      {
        if (!evaluators.empty())
        {
          std::cerr << "Error: The parameter " << param << " cannot be specified more than once!\n";
          return rcInvalidParameter;
        }
        if (argc > i + 1)
        {
          evaluators = std::string(argv[i+1]);
          // Skip next argument, because that was already processed.
          ++i;
        }
        else
        {
          std::cout << "There must be a list of evaluators after " << param << "!\n";
          return rcInvalidParameter;
        }
      }
      else
      {
        std::cerr << "Error: Unknown parameter " << param << "!\n"
                  << "Use --help to show available parameters." << std::endl;
        return rcInvalidParameter;
      }
    }
  } // if arguments are there

  if (!evaluators.empty())
  {
    CompoundEvaluator evaluator;
    // Try to parse user input.
    if (!CompoundCreator::create(evaluators, evaluator))
    {
      std::cout << "Error: The given evaluator list is invalid!\n";
      return rcInvalidParameter;
    }
    // Set custom evaluators.
    Engine::get().setEvaluator(std::move(evaluator));
  }

  // No output buffering.
  disableStdoutBuffering();
  // No input buffering.
  disableStdinBuffering();

  Protocol protocol = Protocol::XBoard;
  try
  {
    protocol = detectProtocolFromStdIn();
  }
  catch(const std::invalid_argument& ex)
  {
    std::cerr << "Error: Invalid first command: '" << ex.what() << "'" << std::endl;
    std::cerr << "The first command should be the protocol's initialization "
              << "command, i. e. 'uci' or 'xboard'." << std::endl;
    return rcEngineProtocolNotSupported;
  }
  switch (protocol)
  {
    case Protocol::UCI:
         uci::CommandParser::parse("uci");
         ParseLoop<uci::CommandParser>();
         break;
    case Protocol::XBoard:
         xboard::CommandParser::parse("xboard");
         ParseLoop<xboard::CommandParser>();
         break;
    default:
         std::cerr << "Error: Unsupported chess protocol detected!" << std::endl
                   << "Hint: Only xboard and UCI protocol are supported." << std::endl;
         return rcEngineProtocolNotSupported;
  }

  return 0;
}
