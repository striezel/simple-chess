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

#include "Engine.hpp"
#include <sstream>
#include "io-utils.hpp"
#include "../evaluation/CheckEvaluator.hpp"
#include "../evaluation/CompoundEvaluator.hpp"
#include "../evaluation/MaterialEvaluator.hpp"
#include "../evaluation/MobilityEvaluator.hpp"
#include "../evaluation/PromotionEvaluator.hpp"
#include "../search/Search.hpp"

namespace simplechess
{

Engine& Engine::get()
{
  static Engine instance;
  return instance;
}

Engine::Engine()
: mQuit(false),
  mProtocolVersion(1), // assume version 1 until we get more information
  mEnginePlayer(Colour::none), // engine plays no side be default
  mBoard(Board()),
  mSearchDepth(1), // default search depth: one ply
  mForceMode(false),
  mTiming(Timing()),
  mQueue(std::deque<std::unique_ptr<Command> >()) // empty queue
{
}

bool Engine::quitRequested() const
{
  return mQuit.load();
}

void Engine::terminate()
{
  mQuit.store(true);
}

unsigned int Engine::protocolVersion() const
{
  return mProtocolVersion;
}

void Engine::setProtocolVersion(const unsigned int protover)
{
  if (protover > 0)
    mProtocolVersion = protover;
  else
    // Minimum allowed version is one.
    mProtocolVersion = 1;
}

Board& Engine::board()
{
  return mBoard;
}

Colour Engine::player() const
{
  return mEnginePlayer;
}

void Engine::setPlayer(const Colour enginePlayer)
{
  mEnginePlayer = enginePlayer;
}

unsigned int Engine::searchDepth() const
{
  return mSearchDepth;
}

void Engine::setSearchDepth(const unsigned int newSearchDepth)
{
  // TODO: Allow higher search depths.
  mSearchDepth = 1;
}

bool Engine::forceMode() const
{
  return mForceMode;
}

void Engine::setForceMode(const bool newForceMode)
{
  mForceMode = newForceMode;
}

Timing& Engine::timing()
{
  return mTiming;
}

void Engine::addCommand(std::unique_ptr<Command>&& com)
{
  if (com != nullptr)
    mQueue.push_back(std::move(com));
}

const std::deque<std::unique_ptr<Command> >& Engine::queue() const
{
  return mQueue;
}

int Engine::processQueue()
{
  int processedCommands = 0;
  while (!mQueue.empty() && !mQuit.load())
  {
    const auto& cmd = mQueue.front();
    cmd->process();
    mQueue.pop_front();
    ++processedCommands;
  } // while
  return processedCommands;
}

void Engine::move()
{
  // Only think about moving, if engine is the one to move.
  if (board().toMove() != player())
    return;

  // Let's find a suitable move.
  Search s(board());
  CompoundEvaluator evaluator;
  // Add the four evaluators we have so far.
  evaluator.add(std::unique_ptr<Evaluator>(new MaterialEvaluator()));
  evaluator.add(std::unique_ptr<Evaluator>(new MobilityEvaluator()));
  evaluator.add(std::unique_ptr<Evaluator>(new PromotionEvaluator()));
  evaluator.add(std::unique_ptr<Evaluator>(new CheckEvaluator()));
  // Search for best move, only one ply. (TODO: Implement variable search depth.)
  s.search(evaluator, 1);
  // Did the search find any moves?
  if (!s.hasMove())
  {
    // No moves have been found. This is probably due to the fact that the
    // engine has been checkmated, so give up here.
    sendCommand("resign");
    return;
  }
  const auto bestMove = s.bestMove();
  const Field from = std::get<0>(bestMove);
  const Field to = std::get<1>(bestMove);
  const PieceType promo = std::get<2>(bestMove);
  // Perform move.
  if (!board().move(from, to, promo))
  {
    // The move the engine found is not allowed. (Should not happen, but who knows?)
    // To avoid any complication, the engine will resign here.
    sendCommand("# The computer move is not allowed. Resigning.");
    if (board().toMove() == Colour::white)
    {
      sendCommand("0-1 {White resigns because it could not find an acceptable move}");
    }
    else
    {
      sendCommand("1-0 {Black resigns because it could not find an acceptable move}");
    }
    return;
  }
  // Send move to xboard.
  std::ostringstream oss;
  oss << "move " << simplechess::column(from) << simplechess::row(from)
      << simplechess::column(to) << simplechess::row(to);
  sendCommand(oss.str());
}

} // namespace
