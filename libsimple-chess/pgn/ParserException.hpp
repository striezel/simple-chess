/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2018  Dirk Stolle

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

#ifndef SIMPLE_CHESS_PGN_PARSEREXCEPTION_HPP
#define SIMPLE_CHESS_PGN_PARSEREXCEPTION_HPP

#include <exception>
#include <string>

namespace simplechess::pgn
{

/** Generic class for PGN parser exceptions. */
class ParserException: public std::exception
{
  public:
    /** \brief Constructor with custom exception message.
     *
     * \param message  the exception message
     */
    ParserException(const std::string& message);


    /** \brief Gets the exception message.
     *
     * \return Returns an explanatory string (C style).
     */
    virtual const char* what() const noexcept;
  private:
    std::string exceptMessage; /**< exception message */
};

} // namespace

#endif // SIMPLE_CHESS_PGN_PARSEREXCEPTION_HPP
