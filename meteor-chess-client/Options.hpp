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

#ifndef SIMPLECHESS_METEOR_CHESS_CLIENT_OPTIONS_HPP
#define SIMPLECHESS_METEOR_CHESS_CLIENT_OPTIONS_HPP

#include <cstdint>
#include <string>

namespace simplechess
{

/** structure for options of meteor-chess-client */
struct MeteorChessOptions
{
  std::string boardId; /**< id of the board in MongoDB */
  std::string hostname; /**< host name of the MongoDB server for meteor-chess */
  uint16_t port; /**< port of the MongoDB server for meteor-chess */
  bool help; /**< whether the program help was requested */
  bool version; /**< whether the version information was requested */
  bool json; /**< whether to produce JSON output */

  /** default constructor */
  MeteorChessOptions();


  /** \brief parses the program options by looking at the program arguments
   *
   * \param argc number of arguments as seen in main() function
   * \param argv array of arguments as seen in main() function
   * \return Returns true, if the arguments could be processed.
   *         Returns false otherwise.
   */
  bool parse(const int argc, char** argv);
}; // struct

} // namespace

#endif // SIMPLECHESS_METEOR_CHESS_CLIENT_OPTIONS_HPP
