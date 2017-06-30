# We might support earlier versions, too, but it's only tested with 2.8.9.
cmake_minimum_required (VERSION 2.8)

project(simple_chess_tests_catch)

set(simple_chess_tests_catch_sources
    ../../data/Board.cpp
    ../../data/Castling.cpp
    ../../data/Field.cpp
    ../../data/ForsythEdwardsNotation.cpp
    ../../data/HalfMove.cpp
    ../../data/Piece.cpp
    ../../data/PortableGameNotation.cpp
    ../../pgn/Parser.cpp
    ../../pgn/ParserException.cpp
    ../../pgn/Token.cpp
    ../../pgn/Tokenizer.cpp
    ../../pgn/UnconsumedTokensException.cpp
    ../../rules/check.cpp
    ../../rules/Moves.cpp
    ../../util/strings.cpp
    testsFEN.cpp
    testsPGN.cpp
    main.cpp)

add_definitions(-std=c++0x)
if (CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-Wall -O3 -fexceptions -std=c++11)
endif (CMAKE_COMPILER_IS_GNUCC)

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(simple_chess_tests_catch ${simple_chess_tests_catch_sources})
