# meteor-chess-client

meteor-chess-client is a utility program that is intended to be used by the
[Meteor Chess](https://github.com/striezel/meteor-chess) game in the future.
It provides some basic functions to support the server of Meteor Chess.

## Invokation

    meteor-chess-client [OPTIONS]

Supported options:

    -? | --help      - shows this help message and exits
    -v | --version   - shows version information and exits
    --board ID       - sets the ID of the chess board that will be read.
                       This parameter is mandatory.
    --host hostname  - host name of the meteor-chess MongoDB server. The default
                       value is localhost.
    --port N         - port number of the meteor-chess MongoDB server. The
                       default value is 3001.
    --json           - print output in JSON format
    --move           - perform move on board and write it back to MongoDB. The
                       default is not to move, but just to print the move.
    --evaluator EVAL - sets a custom set of evaluators to use where EVAL is a
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

## Exit status

* **0** - successful program execution
* **1** - invalid command line parameter
* **7** - error while connecting to, reading from or writing to MongoDB
* **8** - the engine resigned
* **9** - an unknown error occurred
