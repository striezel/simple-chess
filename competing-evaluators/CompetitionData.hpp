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

#ifndef SIMPLE_CHESS_COMPETITION_DATA_HPP
#define SIMPLE_CHESS_COMPETITION_DATA_HPP

#include <string>
#include <map>
#include <memory>
#include <vector>
#include "../data/Result.hpp"
#include "../evaluation/Evaluator.hpp"

namespace simplechess
{

class CompetitionData
{
  public:
    /** \brief Creates data for competition between evaluators.
     *
     * \param allowedEvaluators   ids of allowed evaluators
     */
    CompetitionData(const std::vector<std::string>& allowedEvaluators);


    /** \brief Performs the whole competition between evaluators.
     *
     * \param threads             number of threads to use
     * \remarks At the moment, only single-threaded execution is supported.
     * \return  Returns whether competition was successful.
     */
    bool compete(unsigned int threads = 1);


    /** \brief Shows the competition results on standard output. */
    void show() const;
  private:
    /** \brief Creates all possible compound evaluators using the given evaluators.
     *
     * \param allowedEvaluators  container with identifiers of all allowed evaluators
     * \return Returns a vector containing all combinations.
     */
    static std::vector<std::unique_ptr<Evaluator>> createEvaluators(const std::vector<std::string>& allowedEvaluators);

    /** \brief Sanitizes the given number of threads by looking at the hardware.
     *
     * The given number of threads will be adjusted in place, if it seems to be
     * unreasonable.
     * \param threads   initial number of threads
     */
    static void sanitizeThreadCount(unsigned int& threads);

    /** \brief Performs all games for the competition in a single-threaded way.
     */
    void single_threaded_compete();

    std::vector<std::unique_ptr<Evaluator>> evaluators;
    std::map<unsigned int, unsigned int> wins;
    std::map<unsigned int, unsigned int> defeats;
    std::map<unsigned int, unsigned int> draws;
}; // class

} // namespace

#endif // SIMPLE_CHESS_COMPETITION_DATA_HPP
