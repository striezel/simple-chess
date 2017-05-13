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

#ifndef SIMPLECHESS_PGN_TOKENIZER_HPP
#define SIMPLECHESS_PGN_TOKENIZER_HPP

#include <string>
#include <vector>
#include "Token.hpp"

namespace simplechess
{

namespace pgn
{

/** class that generates a vector of tokens from an input file etc. */
class Tokenizer
{
  public:
      /** \brief gets tokens from a string
       *
       * \param tokenString  the string
       * * \param tokens    the tokens in the string
       * \return Returns a vector of tokens.
       */
    static bool fromString(const std::string& tokenString, std::vector<Token>& tokens);


    /** \brief gets tokens from a file
     *
     * \param fileName  name of the file
     * \param tokens    the tokens in the file
     * \return Returns true in case of success.
     * Returns false, if an error occurred.
     */
    static bool fromFile(const std::string& fileName, std::vector<Token>& tokens);
}; //class

} //namespace

} //namespace

#endif // SIMPLECHESS_PGN_TOKENIZER_HPP
