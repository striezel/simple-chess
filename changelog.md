# History of changes for simple-chess

_Note: This changelog may be incomplete._

## Version 0.5.6 (2021-??-??)

- simple-chess-cli: The program will no longer crash, if the user enters an
  invalid field for a move.

## Version 0.5.5 (2021-05-13)

- The minimum required CMake version to compile the source code is raised from
  version 3.0 to 3.8.
- The C++ standard used during compilation has been raised from C++14 to C++17.
  Recent compilers should support that by now.
- competing-evaluators: initial version of program to let different board
  evaluators compete against each other
- engine: Implement xboard's sd command.

## Version 0.5.4 (2020-01-09)

- meteor-chess-client: use more modern JSON library

## Version 0.5.3 (2019-12-30)
- meteor-chess-client: properly get and set fifty move rule counter when using
  MongoDB data

## Version 0.5.2 (2019-12-29)
The C++ standard used during compilation has been raised from C++11 to C++14.
Most compilers should support that by now.

## Version 0.5.1 (2018-02-16)
- add castling evaluator that gives a malus for not castling before losing the
  possibility to castle
- simple-chess-cli, simple-chess-engine, meteor-chess-client: use castling
  evaluator as part of the default evaluator compound

## Version 0.5.0 (2018-02-15)
- meteor-chess-client: add output field to indicate when engine offers or claims
  a draw (JSON output mode only), and show intention to claim (text output mode
  only), respectively
- simple-chess-engine: implement support for commands setboard and draw

## Version 0.4.1 (2018-02-09)
- meteor-chess-client: give information about pawn promotion, too

## Version 0.4.0 (2018-02-02)
- simple-chess-engine: improved help message text
- engine, meteor-chess-client and simple-chess-cli: new option to set custom
  evaluators to use for finding the best possible move

## Version 0.3.3 (2018-01-31)
- meteor-chess-client: only write move back to MongoDB when told so explicitly
  via command line option --move

## Version 0.3.2 (2018-01-30)
- meteor-chess-client: add possibility to enable JSON output via --json option

## Version 0.3.1 (2018-01-27)
- improve method to determine whether a move is legal, avoiding some false
  positives

## Version 0.3.0 (2018-01-20)
- meteor-chess-client: initial version of engine client for interaction with
  meteor-chess

## Version 0.2.1 (2017-12-28)
- simple-chess-cli: fix incorrect handling of Forsyth-Edwards notation command
  line parameter

## Version 0.2 (2017-12-28)
- improved engine search: increase search depth to two plies

## Version 0.1 (2017-12-27)
- initial, very simple version: engine with only one ply search
