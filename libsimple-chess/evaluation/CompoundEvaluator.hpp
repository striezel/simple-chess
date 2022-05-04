/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2018, 2020, 2022  Dirk Stolle

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

#ifndef SIMPLECHESS_COMPOUNDEVALUATOR_HPP
#define SIMPLECHESS_COMPOUNDEVALUATOR_HPP

#include "Evaluator.hpp"
#include <memory>
#include <vector>

namespace simplechess
{

/** Evaluator that considers the sum of scores of several other evaluators.
 */
class CompoundEvaluator: public Evaluator
{
  public:
    /** \brief Default constructor. Creates an empty CompoundEvaluator.
     */
    CompoundEvaluator();


    /** \brief Evaluates the current situation on the board.
     *
     * \param board  the board that shall be evaluated
     * \return Returns the evaluation of the board in centipawns.
     * Positive values means that white has an advantage, negative values
     * indicate that black has an advantage. Zero means both players are even.
     */
    int score(const Board& board) const override;


    /** \brief Gets the name of the evaluator.
     *
     * \return Returns the name of the evaluator.
     * May contain additional information about the evaluator.
     */
    std::string name() const noexcept override;


    /** \brief Adds another evaluator to the evaluator list.
     *
     * \param eval  the evaluator to add
     */
    void add(std::unique_ptr<Evaluator>&& eval);


    /** \brief Gets the size of the compound, i.e. the number of evaluators in it.
     *
     * \return compound size
     */
    std::size_t size() const noexcept;


    /** \brief Removes all previously added evaluators from the compound.
     */
    void clear() noexcept;


    /** \brief Checks whether the compound is empty.
     *
     * \return true if the compound is empty, false otherwise
     */
    bool empty() const noexcept;
  private:
    std::vector<std::unique_ptr<Evaluator>> evaluators; /**< vector of evaluators to sum up */
}; // class

} // namespace

#endif // SIMPLECHESS_COMPOUNDEVALUATOR_HPP
