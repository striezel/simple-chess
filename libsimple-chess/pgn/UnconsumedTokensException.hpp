/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2018, 2022  Dirk Stolle

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

#ifndef SIMPLE_CHESS_PGN_UNCONSUMEDTOKENSEXCEPTION_HPP
#define SIMPLE_CHESS_PGN_UNCONSUMEDTOKENSEXCEPTION_HPP

#include <vector>
#include "ParserException.hpp"
#include "Token.hpp"

namespace simplechess::pgn
{

/** Specialized exception class of PGN parser for situations where some tokens
    from the PNG could not be processed. */
class UnconsumedTokensException: public ParserException
{
  public:
    /** \brief Constructor.
     *
     * \param _nextIdx  next index that would have been processed
     * \param tokenSize  total number of tokens
     * \param leftOverTokens  tokens that have not been processed
     */
    UnconsumedTokensException(const std::size_t _nextIdx, const std::size_t tokenSize, const std::vector<Token>& leftOverTokens);


    /** \brief Gets the next index that would have been processed.
     *
     * \return next index
     */
    std::size_t nextIndex() const;


    /** \brief Gets the total number of tokens in the original token vector.
     *
     * \return Returns the total number of tokens in the original token vector.
     */
    std::size_t totalTokenCount() const;


    /** \brief Gets the remaining unprocessed tokens.
     *
     * \return Returns the vector of unprocessed tokens.
     */
    const std::vector<Token>& unprocessedTokens() const;
  private:
    std::size_t nextIdx; /**< first unprocessed index */
    std::size_t totalSize; /**< total size of tokens */
    std::vector<Token> remainingTokens; /**< vector of unprocessed tokens */
};

} // namespace

#endif // SIMPLE_CHESS_PGN_UNCONSUMEDTOKENSEXCEPTION_HPP

