# Application code

This directory and its subdirectories contain the code for several applications.

There are the following directories / applications:

* **engine**: XBoard-compatible chess engine that supports most of the XBoard
  commands from protocol version 2
* **meteor-chess-client**: utility program that is intended to be used by the
  [Meteor Chess](https://github.com/striezel/meteor-chess) game
* **pgn-reader**: command-line application that will parse a file containing
 [Portable Game Notation](https://en.wikipedia.org/wiki/Portable_Game_Notation)
 and will then replay that game move by move
* **pgn-reader-with-meteor-chess**: like the "normal" variant of `pgn-reader`,
  but also supports integration with [Meteor Chess](https://github.com/striezel/meteor-chess)
  and can show the game on an instance of Meteor Chess, too
* **simple-chess-cli**: command line interface that allows to play against the
  engine of simple-chess
