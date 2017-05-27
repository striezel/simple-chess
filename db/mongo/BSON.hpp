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

#ifndef SIMPLECHESS_DB_MONGO_BSON_HPP
#define SIMPLECHESS_DB_MONGO_BSON_HPP

#include <string>
#include <utility>
#include <vector>
#include <mongo-client/mongo.h>

namespace simplechess
{

namespace db
{

namespace mongo
{

/** \brief represents a BSON (binary JSON) object
 */
class BSON
{
  public:
    /** \brief default constructor */
    BSON();

    /** destructor */
    ~BSON();


    //delete copy constructor and assignment operator
    BSON(const BSON& other) = delete;
    BSON& operator=(const BSON& other) = delete;


    /** \brief appends a string to the BSON
     *
     * \param key  name of the key
     * \param value  value to append
     * \return Returns true, if the string was appended.
     *         Returns false otherwise.
     */
    bool append(const std::string& key, const std::string& value);


    /** \brief appends a boolean to the BSON
     *
     * \param key  name of the key
     * \param b  value to append
     * \return Returns true, if the boolean was appended.
     *         Returns false otherwise.
     */
    bool append(const std::string& key, const bool b);


    /** \brief appends a double to the BSON
     *
     * \param key  name of the key
     * \param dbl  value to append
     * \return Returns true, if the double was appended.
     *         Returns false otherwise.
     */
    bool append(const std::string& key, const double dbl);


    /** \brief appends a 32 bit integer to the BSON
     *
     * \param key  name of the key
     * \param i32  value to append
     * \return Returns true, if the integer was appended.
     *         Returns false otherwise.
     */
    bool append(const std::string& key, const int32_t i32);


    /** \brief appends a 64 bit integer to the BSON
     *
     * \param key  name of the key
     * \param i64  value to append
     * \return Returns true, if the integer was appended.
     *         Returns false otherwise.
     */
    bool append(const std::string& key, const int64_t i64);


    /** \brief appends a null value to the BSON
     *
     * \param key  name of the key
     * \return Returns true, if null was appended.
     *         Returns false otherwise.
     */
    bool appendNull(const std::string& key);


    /** \brief whether the BSON object is finished
     *
     * \return Returns true, if the BSON is finished. Returns false otherwise.
     */
    bool finished() const;


    /** \brief finishes the BSON object
     *
     * \remarks A finished BSON is a BSON where no more data can be appended.
     * \return Returns true, if the object could be finished.
     */
    bool finish();


    /** \brief gets the keys of this BSON
     *
     * \return vector of key names paired with their type
     */
    std::vector<std::pair<std::string, std::string>> keys() const;


    /** \brief gets the raw underlying pointer
     *
     * \return the bson pointer
     */
    bson* raw() const;
  private:
    bson* mBson; /**< BSON object pointer */
    bool mFinished; /**< whether the object is finished */
}; //class

} //namespace

} //namespace

} //namespace

#endif // SIMPLECHESS_DB_MONGO_BSON_HPP
