# We might support earlier versions, too, but it's only tested with 2.8.9.
cmake_minimum_required (VERSION 2.8)

project(simple_chess_engine)

set(simple_chess_engine_sources
    CommandParser.cpp
    Engine.cpp
    io-utils.cpp
    ../data/Board.cpp
    ../data/Castling.cpp
    ../data/Field.cpp
    ../data/ForsythEdwardsNotation.cpp
    ../data/Piece.cpp
    ../data/Result.cpp
    ../evaluation/CheckEvaluator.cpp
    ../evaluation/CompoundEvaluator.cpp
    ../evaluation/MaterialEvaluator.cpp
    ../evaluation/MobilityEvaluator.cpp
    ../evaluation/PromotionEvaluator.cpp
    ../rules/Moves.cpp
    ../rules/check.cpp
    ../search/Node.cpp
    ../search/Search.cpp
    ../util/GitInfos.cpp
    ../util/strings.cpp
    time/Clock.cpp
    time/Timing.cpp
    xboard/Error.cpp
    xboard/ExactTime.cpp
    xboard/Force.cpp
    xboard/Go.cpp
    xboard/Level.cpp
    xboard/New.cpp
    xboard/NoOperation.cpp
    xboard/Ping.cpp
    xboard/ProtocolVersion.cpp
    xboard/Quit.cpp
    xboard/ResultCmd.cpp
    xboard/SetTime.cpp
    xboard/Usermove.cpp
    main.cpp)

add_definitions(-std=c++11)
if (CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-Wall -O3 -fexceptions -std=c++11)
endif (CMAKE_COMPILER_IS_GNUCC)

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(simple_chess_engine ${simple_chess_engine_sources})

# create git-related constants
# -- get the current commit hash
execute_process(
  COMMAND git rev-parse HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# -- get the commit date
execute_process(
  COMMAND git show -s --format=%ci
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_TIME
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

message("GIT_HASH is ${GIT_HASH}.")
message("GIT_TIME is ${GIT_TIME}.")

# replace git-related constants in GitInfos.cpp
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../util/GitInfos.template.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/../util/GitInfos.cpp
               ESCAPE_QUOTES)
