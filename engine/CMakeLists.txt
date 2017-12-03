# We might support earlier versions, too, but it's only tested with 2.8.9.
cmake_minimum_required (VERSION 2.8)

project(simple_chess_engine)

set(simple_chess_engine_sources
    Engine.cpp
    io-utils.cpp
    ../data/Board.cpp
    ../data/Castling.cpp
    ../data/Field.cpp
    ../data/Piece.cpp
    ../rules/Moves.cpp
    ../rules/check.cpp
    ../util/strings.cpp
    xboard/Error.cpp
    xboard/NoOperation.cpp
    main.cpp)

add_definitions(-std=c++11)
if (CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-Wall -O3 -fexceptions -std=c++11)
endif (CMAKE_COMPILER_IS_GNUCC)

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(simple_chess_engine ${simple_chess_engine_sources})
