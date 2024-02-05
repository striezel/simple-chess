# simple-chess

`simple-chess` provides a collection of a small command-line tools that can be
used to perform some chess-related tasks.

Currently, these are the following programs:

* [`simple-chess-engine`](./simple-chess-engine/readme.md) - XBoard-compatible
  chess engine that supports most of the XBoard commands from protocol version 2
* [`pgn-reader`](./pgn-reader/readme.md) - command-line application that
  parses a file containing a chess game in [Portable Game Notation](https://en.wikipedia.org/wiki/Portable_Game_Notation)
  and will then replay that game move by move
* [`simple-chess-cli`](./simple-chess-cli/readme.md) - program that allows
  to play against the engine of `simple-chess`

## Copyright and Licensing

Copyright 2016 - 2024  Dirk Stolle

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
