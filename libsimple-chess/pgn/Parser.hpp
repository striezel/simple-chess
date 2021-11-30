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

#ifndef SIMPLECHESS_PGN_PARSER_HPP
#define SIMPLECHESS_PGN_PARSER_HPP

#include <vector>
#include "Token.hpp"
#include "../data/PortableGameNotation.hpp"

namespace simplechess
{

namespace pgn
{

/** \brief parses Portable Game Notation
 */
class Parser
{
  public:
    /** \brief parses a portable game notation from a list of tokens
     *
     * \param tokens   vector of tokens
     * \param result   resulting PGN
     * \return Returns true, if parsing was successful. Returns false, if not.
     * \remarks The content of @arg result is undefined, if the method returns false.
     * The method throws ParserException, if something went wrong.
     */
    static bool parse(const std::vector<Token>& tokens, PortableGameNotation& result);
}; //class

} //namespace

} //namespace

#endif // SIMPLECHESS_PGN_PARSER_HPP
