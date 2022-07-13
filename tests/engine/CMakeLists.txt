# We might support earlier versions, too, but try to use a more recent one.
cmake_minimum_required (VERSION 3.8)

project(engine_tests)

set(engine_tests_sources
    ../../engine/Engine.cpp
    ../../engine/io-utils.cpp
    ../../engine/time/Clock.cpp
    ../../engine/time/Timing.cpp
    ../../engine/xboard/CommandParser.cpp
    ../../engine/xboard/Draw.cpp
    ../../engine/xboard/Error.cpp
    ../../engine/xboard/ExactTime.cpp
    ../../engine/xboard/Force.cpp
    ../../engine/xboard/Go.cpp
    ../../engine/xboard/Level.cpp
    ../../engine/xboard/New.cpp
    ../../engine/xboard/Ping.cpp
    ../../engine/xboard/ProtocolVersion.cpp
    ../../engine/xboard/Quit.cpp
    ../../engine/xboard/ResultCmd.cpp
    ../../engine/xboard/SetBoard.cpp
    ../../engine/xboard/SetDepth.cpp
    ../../engine/xboard/SetTime.cpp
    ../../engine/xboard/Usermove.cpp
    ../../engine/xboard/Xboard.cpp
    ../../libsimple-chess/data/Board.cpp
    ../../libsimple-chess/data/Castling.cpp
    ../../libsimple-chess/data/Field.cpp
    ../../libsimple-chess/data/ForsythEdwardsNotation.cpp
    ../../libsimple-chess/data/Piece.cpp
    ../../libsimple-chess/data/Result.cpp
    ../../libsimple-chess/evaluation/CastlingEvaluator.cpp
    ../../libsimple-chess/evaluation/CheckEvaluator.cpp
    ../../libsimple-chess/evaluation/CompoundCreator.cpp
    ../../libsimple-chess/evaluation/CompoundEvaluator.cpp
    ../../libsimple-chess/evaluation/LinearMobilityEvaluator.cpp
    ../../libsimple-chess/evaluation/MaterialEvaluator.cpp
    ../../libsimple-chess/evaluation/PromotionEvaluator.cpp
    ../../libsimple-chess/evaluation/RootMobilityEvaluator.cpp
    ../../libsimple-chess/rules/check.cpp
    ../../libsimple-chess/rules/Moves.cpp
    ../../libsimple-chess/search/Node.cpp
    ../../libsimple-chess/search/Search.cpp
    ../../util/strings.cpp
    xboard/CommandParser.cpp
    main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions(-Wall -Wextra -pedantic -fexceptions)
    if (CODE_COVERAGE)
        add_definitions (-O0)
    else()
        add_definitions (-O3)
    endif()

    set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )
endif ()

add_executable(engine_tests ${engine_tests_sources})

# add test run
add_test(NAME engine-tests
         COMMAND $<TARGET_FILE:engine_tests>)
