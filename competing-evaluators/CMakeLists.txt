# We might support earlier versions, too, but try to use a more recent one.
cmake_minimum_required (VERSION 3.8)

project(competing-evaluators)

set(competing_evaluators_sources
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
    CompetitionData.cpp
    competing.cpp
    main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions(-Wall -O3 -fexceptions)
endif ()

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(competing-evaluators ${competing_evaluators_sources})

target_link_libraries (competing-evaluators "pthread")

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


### tests for competing-evaluators ###

# different invocations for help
add_test(NAME competing-evaluators-help-default
         COMMAND $<TARGET_FILE:competing-evaluators> --help)
add_test(NAME competing-evaluators-help-question-mark
         COMMAND $<TARGET_FILE:competing-evaluators> -?)
add_test(NAME competing-evaluators-help-windows-style
         COMMAND $<TARGET_FILE:competing-evaluators> /?)

# version information
add_test(NAME competing-evaluators-version
         COMMAND $<TARGET_FILE:competing-evaluators> --version)
