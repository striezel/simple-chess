# simple-chess-engine

simple-chess-engine is an XBoard-compatible chess engine that supports most of
the XBoard commands from protocol version 2. The program expects commands from
XBoard on its standard input and prints responses to the standard output.

For the XBoard protocol see
  <https://www.gnu.org/software/xboard/engine-intf.html>.

simple-chess-engine also has incomplete UCI protocol support. The program
expects commands from the UCI-compatible GUI on its standard input and prints
responses to the standard output.
For the UCI protocol specification see
  <http://wbec-ridderkerk.nl/html/UCIProtocol.html>.

## Invocation

    simple-chess-engine [OPTIONS]

Supported program options:
```
  --help | -?      - Shows this help message and exits.
  --version | -v   - Shows version information and exits.
  --evaluator EVAL - Sets a custom set of evaluators to use where EVAL is a
                     comma-separated list of evaluator ids. Valid ids are:
                       material: evaluator using material value of pieces
                       check: evaluator with bonus for checking opponent
                       castling: evaluator with malus for not castling before
                                 the possibility for castling is lost
                       promotion: evaluator with bonus for pawns that can be
                                  promoted during the next move
                       linearmobility: bonus for number of possible moves over
                                       all pieces by a player
                       rootmobility: like linearmobility, but with a slower
                                     increase for higher move numbers
                     A possible use of this option can look like this:
                       --evaluator check,promotion,material
                     If no evaluator option is given, the program uses a preset.
```

## Exit status

* **0** - successful program execution
* **1** - invalid command line parameters have been specified

## Copyright and Licensing

Copyright 2017, 2018, 2019, 2020, 2021, 2022, 2024  Dirk Stolle

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
