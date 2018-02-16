/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2018  Dirk Stolle

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

#ifndef SIMPLECHESS_CASTLINGEVALUATOR_HPP
#define SIMPLECHESS_CASTLINGEVALUATOR_HPP

#include "Evaluator.hpp"

namespace simplechess
{

/** Evaluator that gives a malus when player forfeits the castling opportunity.
 */
class CastlingEvaluator: public Evaluator
{
  public:
    /** The default score for castling in centipawns. */
    static const int defaultCastlingValue;


    /** \brief Constructor with initial value.
     *
     * \param castlingValue value for castling in centipawns
     */
    explicit CastlingEvaluator(const int castlingValue = defaultCastlingValue);


    /** \brief Evaluates the current situation on the board.
     *
     * \param board  the board that shall be evaluated.
     * \return Returns the evaluation of the board in centipawns.
     * Positive values means that white has an advantage, negative values
     * indicate that black has an advantage. Zero means both players are even.
     */
    virtual int score(const Board& board) const;
  private:
    int mCastlingValue; /**< bonus / penalty for castling / not castling in centipawns */
}; // class

} // namespace

#endif // SIMPLECHESS_CASTLINGEVALUATOR_HPP
