cmake_minimum_required (VERSION 3.8)

project(engine_tests)

set(engine_tests_sources
    ../../apps/engine/Engine.cpp
    ../../apps/engine/io-utils.cpp
    ../../apps/engine/time/Clock.cpp
    ../../apps/engine/time/Timing.cpp
    ../../apps/engine/xboard/CommandParser.cpp
    ../../apps/engine/xboard/Draw.cpp
    ../../apps/engine/xboard/Error.cpp
    ../../apps/engine/xboard/ExactTime.cpp
    ../../apps/engine/xboard/Force.cpp
    ../../apps/engine/xboard/Go.cpp
    ../../apps/engine/xboard/Level.cpp
    ../../apps/engine/xboard/New.cpp
    ../../apps/engine/xboard/Ping.cpp
    ../../apps/engine/xboard/ProtocolVersion.cpp
    ../../apps/engine/xboard/Quit.cpp
    ../../apps/engine/xboard/ResultCmd.cpp
    ../../apps/engine/xboard/SetBoard.cpp
    ../../apps/engine/xboard/SetDepth.cpp
    ../../apps/engine/xboard/SetTime.cpp
    ../../apps/engine/xboard/Usermove.cpp
    ../../apps/engine/xboard/Xboard.cpp
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

# MSYS2 / MinGW uses Catch 3.x.
if (HAS_CATCH_V3)
    find_package(Catch2 3 REQUIRED)
    target_link_libraries(engine_tests Catch2::Catch2WithMain)
endif ()

# add test run
add_test(NAME engine-tests
         COMMAND $<TARGET_FILE:engine_tests>)
