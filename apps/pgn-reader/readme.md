# pgn-reader

pgn-reader is a command-line application that will parse a given text file that
contains a chess game in [Portable Game Notation](https://en.wikipedia.org/wiki/Portable_Game_Notation)
(PGN for short) and will then replay that game move by move, showing the chess
board after each move on the standard output.

## Invocation

    pgn-reader --pgn FILENAME [--delay MILLISECONDS]

Supported program options:

```
  --help | -?      - Displays this help message and quits.
  --version | -v   - Shows version information and quits.
  --pgn FILENAME   - Sets the path for the Portable Game Notation file that
                     will be read. This parameter is mandatory.
  --delay N        - Sets the delay between moves to N milliseconds.
                     The default value is 1000, i.e. one second.
```

## Exit status

* **0** - successful program execution
* **1** - invalid command line parameter
* **2** - error during tokenization of PGN file
  (This usually means that the provided PNG file contains some tokens which are
   not recognized by the program.)
* **3** - error while parsing the PGN file
  (This usually means that the provided PNG file contains something that the
   program cannot interpret as Portable Game Notation.)
* **4** - PGN data is implausible
  (This usually means that the provided PNG file may be syntactically valid, but
   it either contains a starting position (specified as FEN) which is invalid or
   contains moves which are not allowed.)
* **6** - impossible move
  (This means that the PGN file contains a move which is impossible / violates
   the chess rules.)

## Copyright and Licensing

Copyright 2017, 2018, 2019, 2021, 2022, 2024  Dirk Stolle

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
