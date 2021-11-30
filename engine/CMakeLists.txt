# We might support earlier versions, too, but try to use a more recent one.
cmake_minimum_required (VERSION 3.8)

project(simple-chess-engine)

set(simple_chess_engine_sources
    Engine.cpp
    io-utils.cpp
    Protocol.cpp
    ../libsimple-chess/data/Board.cpp
    ../libsimple-chess/data/Castling.cpp
    ../libsimple-chess/data/Field.cpp
    ../libsimple-chess/data/ForsythEdwardsNotation.cpp
    ../libsimple-chess/data/Piece.cpp
    ../libsimple-chess/data/Result.cpp
    ../libsimple-chess/evaluation/CastlingEvaluator.cpp
    ../libsimple-chess/evaluation/CheckEvaluator.cpp
    ../libsimple-chess/evaluation/CompoundCreator.cpp
    ../libsimple-chess/evaluation/CompoundEvaluator.cpp
    ../libsimple-chess/evaluation/LinearMobilityEvaluator.cpp
    ../libsimple-chess/evaluation/MaterialEvaluator.cpp
    ../libsimple-chess/evaluation/PromotionEvaluator.cpp
    ../libsimple-chess/evaluation/RootMobilityEvaluator.cpp
    ../libsimple-chess/rules/Moves.cpp
    ../libsimple-chess/rules/check.cpp
    ../libsimple-chess/search/Node.cpp
    ../libsimple-chess/search/Search.cpp
    ../util/GitInfos.cpp
    ../util/strings.cpp
    time/Clock.cpp
    time/Timing.cpp
    uci/CommandParser.cpp
    uci/Go.cpp
    uci/IsReady.cpp
    uci/Move.cpp
    uci/NewGame.cpp
    uci/Position.cpp
    uci/Uci.cpp
    xboard/CommandParser.cpp
    xboard/Draw.cpp
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
    xboard/SetBoard.cpp
    xboard/SetDepth.cpp
    xboard/SetTime.cpp
    xboard/Usermove.cpp
    xboard/Xboard.cpp
    main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions(-Wall -fexceptions)
    if (CODE_COVERAGE)
        add_definitions (-O0)
    else()
        add_definitions (-O3)
    endif()
endif ()

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(simple-chess-engine ${simple_chess_engine_sources})

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


### tests for simple-chess-engine ###

# different invocations for help
add_test(NAME simple-chess-engine-help-default
         COMMAND $<TARGET_FILE:simple-chess-engine> --help)
add_test(NAME simple-chess-engine-help-question-mark
         COMMAND $<TARGET_FILE:simple-chess-engine> -?)
add_test(NAME simple-chess-engine-help-windows-style
         COMMAND $<TARGET_FILE:simple-chess-engine> /?)

# version information
add_test(NAME simple-chess-engine-version
         COMMAND $<TARGET_FILE:simple-chess-engine> --version)
