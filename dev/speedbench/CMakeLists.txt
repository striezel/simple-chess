cmake_minimum_required (VERSION 3.8)

project(speedbench)

set(speedbench_sources
    ../competing-evaluators/competing.cpp
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
    ../../util/GitInfos.cpp
    ../../util/strings.cpp
    main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DSIMPLE_CHESS_NO_COMPETITION_DATA)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions(-Wall -Wextra -pedantic -pedantic-errors -fexceptions)
    if (CODE_COVERAGE)
        add_definitions (-O0)
    else()
        add_definitions (-O3)
    endif()

    set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )
endif ()

add_executable(speedbench ${speedbench_sources})

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
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../../util/GitInfos.template.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/../../util/GitInfos.cpp
               ESCAPE_QUOTES)


### tests for speedbench ###

# different invocations for help
add_test(NAME speedbench-help-default
         COMMAND $<TARGET_FILE:speedbench> --help)
add_test(NAME speedbench-help-question-mark
         COMMAND $<TARGET_FILE:speedbench> -?)
if (NOT DEFINED ENV{GITHUB_ACTIONS} OR NOT MINGW)
    add_test(NAME speedbench-help-windows-style
             COMMAND $<TARGET_FILE:speedbench> /?)
endif ()

# version information
add_test(NAME speedbench-version
         COMMAND $<TARGET_FILE:speedbench> --version)
