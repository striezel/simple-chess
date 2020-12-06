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

#include "competing.hpp"
#include <iostream>
#include <thread>
#include "../data/ForsythEdwardsNotation.hpp"
#include "../evaluation/CompoundCreator.hpp"
#include "../search/Search.hpp"

namespace simplechess
{

const std::vector<std::string> Competition::allEvaluators = {
    CompoundCreator::IdCastling,
    CompoundCreator::IdCheck,
    CompoundCreator::IdLinearMobility,
    CompoundCreator::IdMaterial,
    CompoundCreator::IdPromotion,
    CompoundCreator::IdRootMobility
};

std::vector<std::unique_ptr<Evaluator>> Competition::createEvaluators(const std::vector<std::string>& allowedEvaluators)
{
  const unsigned int distinctCount = allowedEvaluators.size();
  const unsigned int totalCombinations = 1 << allowedEvaluators.size();
  std::vector<std::unique_ptr<Evaluator>> result;
  result.reserve(totalCombinations - 1);
  for (unsigned int i = 1; i < totalCombinations; ++i)
  {
    std::string evals;
    for (unsigned int j = 0; j < distinctCount; ++j)
    {
      if ((i & (1 << j)) != 0)
      {
        evals += "," + allowedEvaluators[j];
      }
    } // for j
    evals = evals.substr(1);
    auto ce_ptr = std::unique_ptr<Evaluator>(new CompoundEvaluator());
    if (!CompoundCreator::create(evals, static_cast<CompoundEvaluator&>(*ce_ptr)))
    {
      return {};
    }
    result.push_back(std::move(ce_ptr));
  } // for i

  return result;
}

void Competition::sanitizeThreadCount(unsigned int& threads)
{
  if (threads == 0)
    threads = 1;
  const unsigned int hw_threads = std::thread::hardware_concurrency();
  if ((hw_threads != 0) && (threads > hw_threads))
  {
    threads = hw_threads;
    std::cout << "Info: Hardware indicates that it only supports " << hw_threads
              << " concurrent threads. Number of threads has been reduced to "
              << hw_threads << "." << std::endl;
  }
}

void Competition::showResults(const std::vector<std::unique_ptr<Evaluator>>& evaluators,
                              const std::map<unsigned int, unsigned int>& wins,
                              const std::map<unsigned int, unsigned int>& defeats,
                              const std::map<unsigned int, unsigned int>& draws)
{
  std::cout << "Win counts:" << std::endl;
  for (const auto& elem : wins)
  {
    std::cout << "Evaluator #" << elem.first << " (" + evaluators[elem.first]->name() + "): " << elem.second << std::endl;
  }

  std::cout << "Defeat counts:" << std::endl;
  for (const auto& elem : defeats)
  {
    std::cout << "Evaluator #" << elem.first << " (" + evaluators[elem.first]->name() + "): " << elem.second << std::endl;
  }

  std::cout << "Draw counts:" << std::endl;
  for (const auto& elem : draws)
  {
    std::cout << "Evaluator #" << elem.first << " (" + evaluators[elem.first]->name() + "): " << elem.second << std::endl;
  }
}

void Competition::single_threaded_compete(const std::vector<std::unique_ptr<Evaluator>>& evaluators,
                                          std::map<unsigned int, unsigned int>& wins,
                                          std::map<unsigned int, unsigned int>& defeats,
                                          std::map<unsigned int, unsigned int>& draws)
{
  const unsigned int totalEvaluators = evaluators.size();
  const unsigned int comboCount = totalEvaluators * (totalEvaluators - 1);

  std::cout << "Info: There are " << totalEvaluators << " different evaluators."
            << std::endl << "This means there will be " << comboCount
            << " different evaluator matches." << std::endl;

  wins.clear();
  defeats.clear();
  draws.clear();

  unsigned int finished = 0;

  for (unsigned int idxWhite = 0; idxWhite < totalEvaluators; ++idxWhite)
  {
    for (unsigned int idxBlack = 0; idxBlack < totalEvaluators; ++idxBlack)
    {
      if (idxWhite == idxBlack)
        continue;

      const Result r = compete(*evaluators[idxWhite], *evaluators[idxBlack]);

      switch (r)
      {
        case Result::WhiteWins:
             ++wins[idxWhite];
             ++defeats[idxBlack];
             break;
        case Result::BlackWins:
             ++wins[idxBlack];
             ++defeats[idxWhite];
             break;
        case Result::Draw:
             ++draws[idxWhite];
             ++draws[idxBlack];
             break;
        case Result::Unknown:
             // do nothing
             break;
      } // switch

      ++finished;

      std::cout << "Progress: " << finished << " of " << comboCount << std::endl;
    } // for idxBlack
  } // for idxWhite
}

void Competition::compete(const std::vector<std::string>& allowedEvaluators, unsigned int threads)
{
  if (allowedEvaluators.empty())
  {
    std::cerr << "No evaluators given!" << std::endl;
    return;
  }
  if (allowedEvaluators.size() > 10)
  {
    std::cerr << "Error: There are more than ten evaluators, this will take an absurd amount of time!" << std::endl;
    return;
  }

  sanitizeThreadCount(threads);
  const auto evaluators = createEvaluators(allowedEvaluators);

  std::map<unsigned int, unsigned int> wins;
  std::map<unsigned int, unsigned int> defeats;
  std::map<unsigned int, unsigned int> draws;

  single_threaded_compete(evaluators, wins, defeats, draws);

  showResults(evaluators, wins, defeats, draws);
}

Result Competition::compete(const Evaluator& white, const Evaluator& black)
{
  Board board;
  if (!board.fromFEN(FEN::defaultInitialPosition))
    return Result::Unknown;

  for ( ; ; )
  {
    if (board.halfmovesFifty() >= 100)
    {
      // Claim draw under 50 move rule to avoid needlessly long games.
      return Result::Draw;
    }

    const auto bestMove = Search::search(board, board.toMove() == Colour::white ? white : black , 2);
    if (std::get<0>(bestMove) == Field::none)
    {
      // Evaluator could not find a valid move. That usually means the player
      // lost, because (s)he's in checkmate. So resign.
      return board.toMove() == Colour::white ? Result::BlackWins : Result::WhiteWins;
    }

    // perform move
    if (!board.move(std::get<0>(bestMove), std::get<1>(bestMove), std::get<2>(bestMove)))
    {
      std::cerr << "Error: Could not perform suggested move!" << std::endl;
      const Field from = std::get<0>(bestMove);
      const Field to = std::get<1>(bestMove);
      std::cerr << "Suggested move was from " << column(from) << row(from)
                << " to " << column(to) << row(to) << " on board with the "
                << "following Forsyth-Edwards notation: " << std::endl;
      std::cerr << FEN::fromBoard(board) << std::endl;
      return Result::Unknown;
    }
  }

  // We should never get to this point.
  return Result::Unknown;
}

} // namespace
