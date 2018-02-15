# simple-chess-engine

simple-chess-engine is an XBoard-compatible chess engine that supports most of
the XBoard commands from protocol version 2. The program expects commands from
XBoard on its standard input and prints responses to the standard output.

For the XBoard protocol see
  <https://www.gnu.org/software/xboard/engine-intf.html>.

## Invocation

    simple-chess-engine [OPTIONS]

Supported program options:

    -? | --help     - shows a help message and exits
    -v | --version  - shows version information and exits
    --evaluator EVAL - sets a custom set of evaluators to use where EVAL is a
                       comma-separated list of evaluator ids. Valid ids are:
                         material: evaluator using material value of pieces
                         check: evaluator with bonus for checking opponent
                         promotion: evaluator with bonus for pawns that can be
                                    promoted during the next move
                         linearmobility: bonus for number of possible moves over
                                         all pieces by a player
                         rootmobility: like linearmobility, but with a slower
                                       increase for higher move numbers
                       A possible use of this option can look like this:
                         --evaluator check,promotion,material
                       If no evaluator option is given, the program uses a preset.

## Exit status

* **0** - successful program execution
* **1** - invalid command line parameters have been specified
