# simple-chess-cli

simple-chess-cli is a command line interface that allows to play against the
engine of simple-chess. Alternatively two human players can play against each
other.

## Invocation

    simple-chess-cli [OPTIONS]

Supported program options:

    -? | --help     - Shows this help message and exits.
    -v | --version  - Shows version information and exits.
    w | white       - Let the engine be the white player.
    b | black       - Let the engine be the black player.
                      (The default is to play none, i.e. both sides are human.)
    FEN             - a valid Forsyth-Edwards notation that indicates the
                      initial position for the chess game. Default is the normal
                      chess start position.
    -e EVAL         - Sets a custom set of evaluators to use where EVAL is a
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
                      Evaluators are used by computer players only, so this
                      has no effect when two humans play against each other.
    --show-labels   - Show labels for fields next to the chess board.
    --hide-labels   - Do not show labels for fields next to the chess board.

## Copyright and Licensing

Copyright 2016, 2017, 2018, 2019, 2020, 2021, 2022  Dirk Stolle

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
