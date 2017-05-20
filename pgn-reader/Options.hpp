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

#ifndef SIMPLECHESS_PGNREADER_OPTIONS_HPP
#define SIMPLECHESS_PGNREADER_OPTIONS_HPP

#include <string>

namespace simplechess
{

/** structure for options of pgn-reader */
struct PgnReaderOptions
{
  std::string inputFile; /**< input file with Portable Game Notation */
  unsigned int delayMilliseconds; /**< delay between moves in milliseconds */


  /** default constructor */
  PgnReaderOptions();


  /** \brief parses the program options by looking at the program arguments
   *
   * \param argc number of arguments as seen in main() function
   * \param argv array of arguments as seen in main() function
   * \return Returns true, if the arguments could be processed.
   *         Returns false otherwise.
   */
  bool parse(const int argc, char** argv);
}; //struct

} //namespace

#endif // SIMPLECHESS_PGNREADER_OPTIONS_HPP
