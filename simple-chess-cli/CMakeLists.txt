# We might support earlier versions, too, but it's only tested with 2.8.9.
cmake_minimum_required (VERSION 2.8)

project(simple_chess_cli)

set(simple_chess_cli_sources
    ../data/board.cpp
    ../data/castling.cpp
    ../data/field.cpp
    ../data/forsyth-edwards-notation.cpp
    ../data/piece.cpp
    ../rules/check.cpp
    ../rules/moves.cpp
    ../ui/Console.cpp
    ../util/strings.cpp
    main.cpp)

add_definitions(-std=c++0x)
if (CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-Wall -O3 -fexceptions -std=c++11)
endif (CMAKE_COMPILER_IS_GNUCC)

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(simple_chess_cli ${simple_chess_cli_sources})
