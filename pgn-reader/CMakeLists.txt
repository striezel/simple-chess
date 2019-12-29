# We might support earlier versions, too, but it's only tested with 2.8.9.
cmake_minimum_required (VERSION 2.8)

project(pgn-reader)

set(pgn_reader_sources
    ../algorithm/Apply.cpp
    ../data/Board.cpp
    ../data/Castling.cpp
    ../data/Field.cpp
    ../data/ForsythEdwardsNotation.cpp
    ../data/HalfMove.cpp
    ../data/Piece.cpp
    ../data/PortableGameNotation.cpp
    ../data/Result.cpp
    ../pgn/Parser.cpp
    ../pgn/ParserException.cpp
    ../pgn/Token.cpp
    ../pgn/Tokenizer.cpp
    ../pgn/UnconsumedTokensException.cpp
    ../rules/check.cpp
    ../rules/Moves.cpp
    ../ui/Console.cpp
    ../util/strings.cpp
    Options.cpp
    main.cpp)

add_definitions(-std=c++14 -DNO_METEOR_CHESS)
if (CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-Wall -O3 -fexceptions -std=c++14)
endif (CMAKE_COMPILER_IS_GNUCC)

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(pgn-reader ${pgn_reader_sources})


# # # tests for pgn-reader # # #

# different invocations for help
add_test(NAME pgn-reader-help-default
         COMMAND $<TARGET_FILE:pgn-reader> --help)
add_test(NAME pgn-reader-help-question-mark
         COMMAND $<TARGET_FILE:pgn-reader> -?)
add_test(NAME pgn-reader-help-windows-style
         COMMAND $<TARGET_FILE:pgn-reader> /?)

# version information
add_test(NAME pgn-reader-version
         COMMAND $<TARGET_FILE:pgn-reader> --version)

# test run with example PGN file, 1 ms delay (to keep test fast)
add_test(NAME pgn-reader-steinitz
         COMMAND $<TARGET_FILE:pgn-reader> --pgn ${CMAKE_CURRENT_SOURCE_DIR}/examples/steinitz1887.pgn --delay 1)
