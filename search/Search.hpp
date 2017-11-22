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

#ifndef SIMPLECHESS_SEARCH_HPP
#define SIMPLECHESS_SEARCH_HPP

#include "../data/Board.hpp"
#include "../evaluation/Evaluator.hpp"
#include "Node.hpp"

namespace simplechess
{

/** Provides methods to search for best move. */
class Search
{
  public:
    /** \brief Searches for the best move.
     *
     * \param board the current position
     * \param eval evaluator for positions
     * \param depth search depth
     */
    static Node search(const Board& board, const Evaluator& eval, const unsigned int depth);
  private:
    /** \brief Creates child nodes for a given node.
     *
     * \param node current node that will be expanded
     * \param eval evaluator for positions
     * \param depth search depth
     */
    static void expandNode(Node& node, const Evaluator& eval, const unsigned int depth);
}; //class

} //namespace

#endif // SIMPLECHESS_SEARCH_HPP
