/*
 -------------------------------------------------------------------------------
    This file is part of simple-chess.
    Copyright (C) 2017, 2024  Dirk Stolle

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

#ifndef SIMPLE_CHESS_PGNREADER_OPTIONS_HPP
#define SIMPLE_CHESS_PGNREADER_OPTIONS_HPP

#include <cstdint>
#include <optional>
#include <string>
#include "../../libsimple-chess/ui/Console.hpp"

namespace simplechess
{

/** structure for options of pgn-reader */
struct PgnReaderOptions
{
  std::string inputFile; /**< input file with Portable Game Notation */
  unsigned int delayMilliseconds; /**< delay between moves in milliseconds */
  bool help; /**< whether the program help was requested */
  bool version; /**< whether the version information was requested */
  std::optional<ui::PieceGlyphs> glyphs; /**< what glyphs to use for pieces */
  #ifndef NO_METEOR_CHESS
  bool meteorChess; /**< whether meteor-chess will be used for output */
  std::string hostname; /**< host name of the MongoDB server for meteor-chess */
  uint16_t port; /**< port of the MongoDB server for meteor-chess */
  #endif // NO_METEOR_CHESS


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

#endif // SIMPLE_CHESS_PGNREADER_OPTIONS_HPP
