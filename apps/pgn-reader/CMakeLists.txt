cmake_minimum_required (VERSION 3.8...3.31)

project(pgn-reader)

set(pgn_reader_sources
    ../../libsimple-chess/algorithm/Apply.cpp
    ../../libsimple-chess/data/Board.cpp
    ../../libsimple-chess/data/Castling.cpp
    ../../libsimple-chess/data/Field.cpp
    ../../libsimple-chess/data/ForsythEdwardsNotation.cpp
    ../../libsimple-chess/data/HalfMove.cpp
    ../../libsimple-chess/data/Piece.cpp
    ../../libsimple-chess/data/PortableGameNotation.cpp
    ../../libsimple-chess/data/Result.cpp
    ../../libsimple-chess/pgn/Parser.cpp
    ../../libsimple-chess/pgn/ParserException.cpp
    ../../libsimple-chess/pgn/Token.cpp
    ../../libsimple-chess/pgn/Tokenizer.cpp
    ../../libsimple-chess/pgn/UnconsumedTokensException.cpp
    ../../libsimple-chess/rules/check.cpp
    ../../libsimple-chess/rules/Moves.cpp
    ../../libsimple-chess/ui/Console.cpp
    ../../libsimple-chess/ui/detect_utf8.cpp
    ../../libsimple-chess/ui/letters.hpp
    ../../libsimple-chess/ui/symbols.hpp
    ../../util/GitInfos.cpp
    ../../util/strings.cpp
    ../../util/Version.cpp
    Options.cpp
    main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DNO_METEOR_CHESS)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions(-Wall -Wextra -pedantic -pedantic-errors -fexceptions)
    if (CODE_COVERAGE)
        add_definitions (-O0)
    else()
        add_definitions (-O3)
    endif()

    set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )
endif ()

add_executable(pgn-reader ${pgn_reader_sources})

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

# # # tests for pgn-reader # # #

# different invocations for help
add_test(NAME pgn-reader-help-default
         COMMAND $<TARGET_FILE:pgn-reader> --help)
add_test(NAME pgn-reader-help-question-mark
         COMMAND $<TARGET_FILE:pgn-reader> -?)
if (NOT DEFINED ENV{GITHUB_ACTIONS} OR NOT MINGW)
    add_test(NAME pgn-reader-help-windows-style
             COMMAND $<TARGET_FILE:pgn-reader> /?)
endif ()

# version information
add_test(NAME pgn-reader-version
         COMMAND $<TARGET_FILE:pgn-reader> --version)

# test run with example PGN file, 1 ms delay (to keep test fast)
add_test(NAME pgn-reader-steinitz
         COMMAND $<TARGET_FILE:pgn-reader> --pgn ${CMAKE_CURRENT_SOURCE_DIR}/examples/steinitz1887.pgn --delay 1)
