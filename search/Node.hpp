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

#ifndef SIMPLECHESS_NODE_HPP
#define SIMPLECHESS_NODE_HPP

#include <memory>
#include <vector>
#include "../data/Board.hpp"
#include "../data/HalfMove.hpp"

namespace simplechess
{

struct Node
{
  public:
    /** \brief Default constructor.
     */
    Node();


    /** \brief Constructor with initial values.
     *
     * \param b the current board
     * \param hm half move
     * \param score  the score of the node
     */
    Node(const Board& b, const HalfMove& hm, const int score);


    Board board; /**< current board for position at that node */
    HalfMove move; /**< half move that led to the current position */
    int score; /**< score of the position */
    std::vector<std::unique_ptr<Node>> children; /**< pointers to child nodes */


    /** \brief Sorts the children by score.
     */
    void sortChildren();
}; //class

} //namespace

#endif // SIMPLECHESS_NODE_HPP
