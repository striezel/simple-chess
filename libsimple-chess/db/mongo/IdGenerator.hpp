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

#ifndef SIMPLECHESS_DB_MONGO_IDGENERATOR_HPP
#define SIMPLECHESS_DB_MONGO_IDGENERATOR_HPP

#include <string>
#include <vector>

namespace simplechess::db::mongo
{

/** Class to generate a random string ID. */
class IdGenerator
{
  public:
    /** \brief Generates a random string ID.
     *
     * \return Returns the generated string.
     */
    static std::string generate();


    /** \brief Generates a random string ID, avoiding existing IDs.
     *
     * \param existingIds  a vector of already existing IDs
     * \return Returns the generated string.
     */
    static std::string generate(const std::vector<std::string>& existingIds);
}; // class

} // namespace

#endif // SIMPLECHESS_DB_MONGO_IDGENERATOR_HPP
