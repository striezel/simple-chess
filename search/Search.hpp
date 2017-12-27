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

#include <tuple>
#include "../data/Board.hpp"
#include "../evaluation/Evaluator.hpp"
#include "Node.hpp"

namespace simplechess
{

/** Provides methods to search for best move. */
class Search
{
  public:
    /** \brief Constructor.
     *
     * \param board the current position
     */
    Search(const Board& board);


    /** \brief Searches for the best move from the current position.
     *
     * \param eval evaluator for positions
     * \param depth search depth
     * \remarks Call bestMove() afterwards to get the best move from the search.
     */
    void search(const Evaluator& eval, const unsigned int depth);


    /** \brief Checks whether the search result (if any) has a possible move.
     *
     * \return Returns true, if there is a move. Returns false otherwise.
     */
    bool hasMove() const;


    /** \brief Gets the best move (if any moves are available).
     *
     * \return Returns a tuple (origin, destination, promotion type) indicating the best move.
     *         Returns (Field::none, Field::none, PieceType::none) if there is no best move.
     * \remarks You need to call search(eval, depth) before calling bestMove().
     */
    std::tuple<Field, Field, PieceType> bestMove() const;


    /** \brief Gets the root node of the search.
     *
     * \return Returns a constant reference to the root node of the search tree.
     */
    const Node& rootNode() const;


    /** \brief Gets the depth of the last search in number of plys / half moves.
     *
     * \return Returns the depth of the last search, or zero if no search has
     *         been performed by this instance yet.
     */
    unsigned int depth() const;


    /** \brief Searches for the best next move on the given board.
     *
     * \param board the current position
     * \param eval evaluator for positions
     * \param depth search depth
     * \return Returns a tuple (origin, destination, promotion type) indicating the best move.
     *         Returns (Field::none, Field::none, PieceType::none) if there is no best move.
     */
    static std::tuple<Field, Field, PieceType> search(const Board& board, const Evaluator& eval, const unsigned int depth);
  private:
    /** \brief Creates child nodes for a given node.
     *
     * \param node current node that will be expanded
     * \param eval evaluator for positions
     * \param depth search depth
     */
    static void expandNode(Node& node, const Evaluator& eval, const unsigned int depth);


    Node root; /**< root node of search for the current starting position */
    unsigned int searchDepth; /**< depth of last search in plys / half moves */
}; //class

} //namespace

#endif // SIMPLECHESS_SEARCH_HPP
