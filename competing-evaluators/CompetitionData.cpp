/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2020, 2021  Dirk Stolle

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

#include "CompetitionData.hpp"
#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>
#include "../data/ForsythEdwardsNotation.hpp"
#include "../evaluation/CompoundCreator.hpp"
#include "../search/Search.hpp"
#include "competing.hpp"

namespace simplechess
{

CompetitionData::CompetitionData(const std::vector<std::string>& allowedEvaluators)
: stopRequested(false),
  isCompeting(false),
  evaluators(createEvaluators(allowedEvaluators)),
  wins(),
  defeats(),
  draws()
{
}

std::vector<std::unique_ptr<Evaluator>> CompetitionData::createEvaluators(const std::vector<std::string>& allowedEvaluators)
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

void CompetitionData::sanitizeThreadCount(unsigned int& threads)
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

void CompetitionData::show() const
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

void CompetitionData::single_threaded_compete()
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
      if (stopRequested)
      {
        return;
      }
      if (idxWhite == idxBlack)
        continue;
      const Result r = Competition::compete(*evaluators[idxWhite], *evaluators[idxBlack]);

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

void CompetitionData::multi_threaded_compete(unsigned int threads)
{
  const unsigned int totalEvaluators = evaluators.size();
  const unsigned int comboCount = totalEvaluators * (totalEvaluators - 1);

  std::cout << "Info: There are " << totalEvaluators << " different evaluators."
            << std::endl << "This means there will be " << comboCount
            << " different evaluator matches." << std::endl;

  wins.clear();
  defeats.clear();
  draws.clear();

  std::atomic<unsigned int> finished(0);
  std::mutex mutuallyExclusive;

  if (threads > totalEvaluators)
  {
    threads = totalEvaluators;
  }

  const auto perThread = totalEvaluators / threads;

  for (unsigned int idxWhite = 0; idxWhite < totalEvaluators; ++idxWhite)
  {
    if (stopRequested)
    {
      return;
    }

    const auto lambda = [&] (const unsigned int startIdx, const unsigned int endIdx)
    {
      for (unsigned int idxBlack = startIdx; idxBlack < endIdx; ++idxBlack)
      {
        if (stopRequested)
        {
          std::clog << "Exiting thread due to stop request." << std::endl;
          return;
        }
        if (idxWhite == idxBlack)
          continue;
        const Result r = Competition::compete(*evaluators[idxWhite], *evaluators[idxBlack]);

        {
          std::lock_guard<std::mutex> guard(mutuallyExclusive);
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
        } // scope for lock guard
      } // for idxBlack
    };

    // create threads
    std::vector<std::thread> actualThreads;
    for (unsigned int i = 0; i < threads - 1; ++i)
    {
      actualThreads.push_back(std::thread(lambda, i * perThread, (i+1) * perThread));
    }
    // Last thread does a bit more, if number of threads is not a factor of totalEvaluators.
    actualThreads.push_back(std::thread(lambda, (threads-1) * perThread, totalEvaluators));

    // Join all threads.
    for (auto& t : actualThreads)
    {
      t.join();
    }
  } // for idxWhite
}

bool CompetitionData::compete(unsigned int threads)
{
  if (evaluators.empty())
  {
    std::cerr << "No evaluators given!" << std::endl;
    return false;
  }
  if (evaluators.size() > 1024)
  {
    std::cerr << "Error: There are more than 1024 evaluators, this will take an absurd amount of time!" << std::endl;
    return false;
  }

  isCompeting = true;
  sanitizeThreadCount(threads);
  if (threads == 1)
  {
    std::cout << "Starting single-threaded run." << std::endl;
    single_threaded_compete();
  }
  else
  {
    std::cout << "Starting multi-threaded run with " << threads << " threads." << std::endl;
    multi_threaded_compete(threads);
  }
  isCompeting = false;

  return true;
}

void CompetitionData::requestStop()
{
  stopRequested = true;
}

void CompetitionData::waitForStop()
{
  if (!stopRequested || !isCompeting)
    return;

  unsigned int waits = 0;
  // Note: This does not quite work as expected (yet).
  while (isCompeting && waits < 60)
  {
    std::this_thread::yield();
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    ++waits;
  }
}

} // namespace
