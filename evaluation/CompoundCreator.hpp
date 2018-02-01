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

#ifndef SIMPLECHESS_COMPOUNDCREATOR_HPP
#define SIMPLECHESS_COMPOUNDCREATOR_HPP

#include <string>
#include "CompoundEvaluator.hpp"

namespace simplechess
{

/** \brief Utility class to create compound evaluators. */
class CompoundCreator
{
  public:
    /** \brief Creates a compound evaluator based on the evaluator identifiers given.
     *
     * \param evaluators comma-separated list of evaluator identifiers
     * \param compound  CompoundEvaluator that will be used to store evaluators
     * \return Returns true, if the creation of the compound evaluator was successful.
     *         Returns false, if the creation of the compound evaluator failed.
     * \remarks Should change return type to std::optional, once the C++17 support
     *          hits all major compilers in major distributions.
     */
    static bool create(const std::string& evaluators, CompoundEvaluator& compound);


    /** \brief Creates the default compound evaluator used in simple-chess.
     *
     * \param compound  CompoundEvaluator that will be used to store evaluators
     */
    static void getDefault(CompoundEvaluator& compound);


    static const std::string IdCheck; /**< id for CheckEvaluator */
    static const std::string IdLinearMobility; /**< id for LinearMobilityEvaluator */
    static const std::string IdMaterial; /**< id for MaterialEvaluator */
    static const std::string IdPromotion; /**< id for PromotionEvaluator */
    static const std::string IdRootMobility; /**< id for RootMobilityEvaluator */
  private:
    /** \brief Private constructor, because class shall not be instantiated.
     */
    CompoundCreator();
}; // class

} // namespace

#endif // SIMPLECHESS_COMPOUNDCREATOR_HPP
