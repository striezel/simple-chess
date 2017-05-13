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

#ifndef SIMPLECHESS_PGN_TOKEN_HPP
#define SIMPLECHESS_PGN_TOKEN_HPP

#include<string>
#include "TokenType.hpp"

namespace simplechess
{

namespace pgn
{

/** \brief represents a single token in Portable Game Notation
 */
struct Token
{
  /** \brief default constructor, constructs empty token */
  Token();


  /** \brief constructor with initial values
   *
   * \param _type  token type
   * \param content   content of the token
   */
  Token(TokenType _type, const std::string& content);

  TokenType type; /**< type of the token */
  std::string text; /**< content of the token (if not already defined by type) */
};

} //namespace

} //namespace

#endif // SIMPLECHESS_PGN_TOKEN_HPP
