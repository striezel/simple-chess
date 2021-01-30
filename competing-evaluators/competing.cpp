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

#include "competing.hpp"
#include <iostream>
#include <thread>
#include "../data/ForsythEdwardsNotation.hpp"
#include "../evaluation/CompoundCreator.hpp"
#include "../search/Search.hpp"
#ifndef SIMPLECHESS_NO_COMPETITION_DATA
#include "CompetitionData.hpp"
#endif

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

#ifndef SIMPLECHESS_NO_COMPETITION_DATA
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

  CompetitionData data(allowedEvaluators);
  if (data.compete())
  {
    data.show();
  }
  else
  {
    std::cerr << "Could not start evaluator competition!" << std::endl;
  }
}
#endif

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
