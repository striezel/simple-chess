/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2018, 2021, 2025  Dirk Stolle

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

#ifndef SIMPLE_CHESS_COMPOUNDCREATOR_HPP
#define SIMPLE_CHESS_COMPOUNDCREATOR_HPP

#include <string_view>
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
    static bool create(const std::string_view evaluators, CompoundEvaluator& compound);


    /** \brief Creates the default compound evaluator used in simple-chess.
     *
     * \param compound  CompoundEvaluator that will be used to store evaluators
     */
    static void getDefault(CompoundEvaluator& compound);


    static constexpr std::string_view IdCastling = "castling"; /**< id for CastlingEvaluator */
    static constexpr std::string_view IdCheck = "check"; /**< id for CheckEvaluator */
    static constexpr std::string_view IdLinearMobility = "linearmobility"; /**< id for LinearMobilityEvaluator */
    static constexpr std::string_view IdMaterial = "material"; /**< id for MaterialEvaluator */
    static constexpr std::string_view IdPromotion = "promotion"; /**< id for PromotionEvaluator */
    static constexpr std::string_view IdRootMobility = "rootmobility"; /**< id for RootMobilityEvaluator */
  private:
    /** \brief Deleted constructor, because class shall not be instantiated.
     */
    CompoundCreator() = default;
}; // class

} // namespace

#endif // SIMPLE_CHESS_COMPOUNDCREATOR_HPP
