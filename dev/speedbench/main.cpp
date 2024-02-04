/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2021  Dirk Stolle

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

#include <chrono>
#include <iostream>
#include "../competing-evaluators/competing.hpp"
#include "../../libsimple-chess/evaluation/CompoundEvaluator.hpp"
#include "../../libsimple-chess/evaluation/CastlingEvaluator.hpp"
#include "../../libsimple-chess/evaluation/CheckEvaluator.hpp"
#include "../../libsimple-chess/evaluation/LinearMobilityEvaluator.hpp"
#include "../../libsimple-chess/evaluation/MaterialEvaluator.hpp"
#include "../../libsimple-chess/evaluation/PromotionEvaluator.hpp"
#include "../../libsimple-chess/evaluation/RootMobilityEvaluator.hpp"
#include "../../util/GitInfos.hpp"
#include "../../util/ReturnCodes.hpp"
#include "../../util/Version.hpp"

void showVersion()
{
  simplechess::GitInfos info;
  std::cout << "simple-chess-speedbench, " << simplechess::version << "\n"
            << "\n"
            << "Version control commit: " << info.commit() << "\n"
            << "Version control date:   " << info.date() << std::endl;
}

void showHelp()
{
  std::cout << "simple-chess-speedbench [OPTIONS]\n"
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
        return rcInvalidParameter;
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
        return rcInvalidParameter;
      }
    } // for i
  } // if arguments are there

  std::cout << "Sizes of types:"
            << "\nField:    " << sizeof(Field)
            << "\nColour:   " << sizeof(Colour)
            << "\nPiece:    " << sizeof(Piece)
            << "\nCastling: " << sizeof(Castling)
            << "\nBoard:    " << sizeof(Board)
            << "\nuns. int: " << sizeof(unsigned int)
            << "\nbool:     " << sizeof(bool)
            << std::endl;

  CompoundEvaluator compoundL;
  compoundL.add(std::unique_ptr<Evaluator>(new MaterialEvaluator()));
  compoundL.add(std::unique_ptr<Evaluator>(new LinearMobilityEvaluator()));
  compoundL.add(std::unique_ptr<Evaluator>(new PromotionEvaluator()));
  compoundL.add(std::unique_ptr<Evaluator>(new CheckEvaluator()));
  compoundL.add(std::unique_ptr<Evaluator>(new CastlingEvaluator()));
  CompoundEvaluator compoundR;
  compoundR.add(std::unique_ptr<Evaluator>(new MaterialEvaluator()));
  compoundR.add(std::unique_ptr<Evaluator>(new RootMobilityEvaluator()));
  compoundR.add(std::unique_ptr<Evaluator>(new PromotionEvaluator()));
  compoundR.add(std::unique_ptr<Evaluator>(new CheckEvaluator()));
  compoundR.add(std::unique_ptr<Evaluator>(new CastlingEvaluator()));
  std::cout << "Starting two games..."
            << std::endl;
  const auto start = std::chrono::steady_clock::now();
  simplechess::Competition::compete(compoundL, compoundR);
  simplechess::Competition::compete(compoundR, compoundL);
  const auto end = std::chrono::steady_clock::now();
  auto duration = end - start;
  auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
  std::cout << "Finished.\nDuration: " << nanos.count() << " ns" << std::endl;
  return 0;
}
