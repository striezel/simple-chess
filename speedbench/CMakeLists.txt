# We might support earlier versions, too, but those have not been tested.
cmake_minimum_required (VERSION 2.8)

project(speedbench)

set(speedbench_sources
    ../competing-evaluators/competing.cpp
    ../data/Board.cpp
    ../data/Castling.cpp
    ../data/Field.cpp
    ../data/ForsythEdwardsNotation.cpp
    ../data/Piece.cpp
    ../data/Result.cpp
    ../evaluation/CastlingEvaluator.cpp
    ../evaluation/CheckEvaluator.cpp
    ../evaluation/CompoundCreator.cpp
    ../evaluation/CompoundEvaluator.cpp
    ../evaluation/LinearMobilityEvaluator.cpp
    ../evaluation/MaterialEvaluator.cpp
    ../evaluation/PromotionEvaluator.cpp
    ../evaluation/RootMobilityEvaluator.cpp
    ../rules/check.cpp
    ../rules/Moves.cpp
    ../search/Node.cpp
    ../search/Search.cpp
    ../util/GitInfos.cpp
    ../util/strings.cpp
    main.cpp)

add_definitions(-std=c++14 -O3 -DSIMPLECHESS_NO_COMPETITION_DATA)
if (CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-Wall -O3 -fexceptions -std=c++14)
endif (CMAKE_COMPILER_IS_GNUCC)

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

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
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../util/GitInfos.template.cpp
               ${CMAKE_CURRENT_SOURCE_DIR}/../util/GitInfos.cpp
               ESCAPE_QUOTES)


### tests for speedbench ###

# different invocations for help
add_test(NAME speedbench-help-default
         COMMAND $<TARGET_FILE:speedbench> --help)
add_test(NAME speedbench-help-question-mark
         COMMAND $<TARGET_FILE:speedbench> -?)
add_test(NAME speedbench-help-windows-style
         COMMAND $<TARGET_FILE:speedbench> /?)

# version information
add_test(NAME speedbench-version
         COMMAND $<TARGET_FILE:speedbench> --version)
