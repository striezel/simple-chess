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

namespace simplechess
{

Engine& Engine::get()
{
  static Engine instance;
  return instance;
}

Engine::Engine()
: mProtocolVersion(1), // assume version 1 until we get more information
  mEnginePlayer(Colour::none), // engine plays no side be default
  mBoard(Board()),
  mSearchDepth(1), // default search depth: one ply
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

} // namespace
