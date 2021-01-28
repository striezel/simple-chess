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

#ifndef SIMPLE_CHESS_COMPETING_HPP
#define SIMPLE_CHESS_COMPETING_HPP

#include <string>
#include <map>
#include <memory>
#include <vector>
#include "../data/Result.hpp"
#include "../evaluation/Evaluator.hpp"

namespace simplechess
{

/** \brief Wraps all main methods required for competing evaluators.
 */
class Competition
{
  public:
    /** \brief container with identifiers for all available evaluators
     */
    static const std::vector<std::string> allEvaluators;


    /** \brief Performs the whole competition between evaluators.
     *
     * \param allowedEvaluators   ids of allowed evaluators
     * \param threads             number of threads to use
     * \remarks At the moment, only single-threaded execution is supported.
     */
    static void compete(const std::vector<std::string>& allowedEvaluators, unsigned int threads = 1);


    /** \brief Starts a new game with two competing evaluators.
     *
     * \param white   evaluator for the white player
     * \param black   evaluator for the black player
     * \return Returns the result of the game.
     *         Returns Result::Unknown, if an error occurred.
     */
    static Result compete(const Evaluator& white, const Evaluator& black);
  private:
    /** \brief Creates all possible compound evaluators using the given evaluators.
     *
     * \param allowedEvaluators  container with identifiers of all allowed evaluators
     * \return Returns a vector containing all combinations.
     */
    static std::vector<std::unique_ptr<Evaluator>> createEvaluators(const std::vector<std::string>& allowedEvaluators);


    /** \brief Performs all games for the competition in a single-threaded way.
     *
     * \param evaluators   the different evaluators that compete
     * \param wins         map used to store win counts
     * \param defeats      map used to store defeat counts
     * \param draws        map used to store draw counts
     */
    static void single_threaded_compete(const std::vector<std::unique_ptr<Evaluator>>& evaluators,
                                        std::map<unsigned int, unsigned int>& wins,
                                        std::map<unsigned int, unsigned int>& defeats,
                                        std::map<unsigned int, unsigned int>& draws);

    /** \brief Sanitizes the given number of threads by looking at the hardware.
     *
     * The given number of threads will be adjusted in place, if it seems to be
     * unreasonable.
     * \param threads   initial number of threads
     */
    static void sanitizeThreadCount(unsigned int& threads);


    /** \brief Shows the competition results on standard output.
     *
     * \param evaluators   the different evaluators that competed
     * \param wins         map used to store win counts
     * \param defeats      map used to store defeat counts
     * \param draws        map used to store draw counts
     */
    static void showResults(const std::vector<std::unique_ptr<Evaluator>>& evaluators,
                            const std::map<unsigned int, unsigned int>& wins,
                            const std::map<unsigned int, unsigned int>& defeats,
                            const std::map<unsigned int, unsigned int>& draws);
}; // class

} // namespace

#endif // SIMPLE_CHESS_COMPETING_HPP
