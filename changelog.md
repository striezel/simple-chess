# History of changes for simple-chess

_Note: This changelog may be incomplete._

## Next version (2018-??-??)
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
  line paramater

## Version 0.2 (2017-12-28)
- improved engine search: increase search depth to two plies

## Version 0.1 (2017-12-27)
- initial, very simple version: engine with only one ply search
