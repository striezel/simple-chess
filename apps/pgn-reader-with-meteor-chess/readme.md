# pgn-reader with support for Meteor Chess

pgn-reader is a command-line application that will parse a given text file that
contains a chess game in [Portable Game Notation](https://en.wikipedia.org/wiki/Portable_Game_Notation)
(PGN for short) and will then replay that game move by move, showing the chess
board after each move on the standard output.

Additionally to the "normal" version of `pgn-reader`, this variant supports
integration with [Meteor Chess](https://github.com/striezel/meteor-chess) and
also displays the game and moves from the parsed PGN file in the specified
instance of Meteor Chess.

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
  --letters        - Use letters to represent chess pieces on the board.
                     Use this option, if your terminal cannot display UTF-8
                     characters properly. Mutually exclusive with --symbols.
  --symbols        - Use symbols to represent chess pieces on the board. This
                     option requires that the terminal supports UTF-8. While it
                     may look nicer, not all terminals support it. This option
                     is mutually exclusive with --letters.
  --meteor-chess   - Displays board in meteor-chess instance, too.
  --host hostname  - Sets host name of the meteor-chess MongoDB server.
                     The default value is "localhost".
  --port N         - Sets port number of the meteor-chess MongoDB server.
                     The default value is 3001.
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
