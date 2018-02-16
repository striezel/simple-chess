# simple-chess-cli

simple-chess-cli is a command line interface that allows to play against the
engine of simple-chess. Alternatively two human players can play against each
other.

## Invocation

    simple-chess-cli [OPTIONS]

Supported program options:

    -? | --help     - shows this help message and exits
    -v | --version  - shows version information and exits
    w | white       - let the engine be the white player
    b | black       - let the engine be the black player
                      (The default is to play none, i.e. both sides are human.)
    FEN             - a valid Forsyth-Edwards notation that indicates the
                      initial position for the chess game. Default is the normal
                      chess start position.
    -e EVAL         - sets a custom set of evaluators to use where EVAL is a
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
