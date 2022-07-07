# We might support earlier versions, too, but try to use a more recent one.
cmake_minimum_required (VERSION 3.8)

project(pgn-reader-with-meteor-chess)

set(pgn_reader_with_meteor_chess_sources
    ../libsimple-chess/algorithm/Apply.cpp
    ../libsimple-chess/data/Board.cpp
    ../libsimple-chess/data/Castling.cpp
    ../libsimple-chess/data/Field.cpp
    ../libsimple-chess/data/ForsythEdwardsNotation.cpp
    ../libsimple-chess/data/HalfMove.cpp
    ../libsimple-chess/data/Piece.cpp
    ../libsimple-chess/data/PortableGameNotation.cpp
    ../libsimple-chess/data/Result.cpp
    ../libsimple-chess/db/mongo/Convert.cpp
    ../libsimple-chess/db/mongo/IdGenerator.cpp
    ../libsimple-chess/db/mongo/libmongoclient/BSON.cpp
    ../libsimple-chess/db/mongo/libmongoclient/Connection.cpp
    ../libsimple-chess/db/mongo/libmongoclient/QueryCursor.cpp
    ../libsimple-chess/db/mongo/libmongoclient/Server.cpp
    ../libsimple-chess/pgn/Parser.cpp
    ../libsimple-chess/pgn/ParserException.cpp
    ../libsimple-chess/pgn/Token.cpp
    ../libsimple-chess/pgn/Tokenizer.cpp
    ../libsimple-chess/pgn/UnconsumedTokensException.cpp
    ../libsimple-chess/rules/check.cpp
    ../libsimple-chess/rules/Moves.cpp
    ../libsimple-chess/ui/Console.cpp
    ../libsimple-chess/ui/SymbolicBoard.cpp
    ../libsimple-chess/ui/detect_utf8.cpp
    ../libsimple-chess/ui/letters.hpp
    ../libsimple-chess/ui/symbols.hpp
    ../util/strings.cpp
    ../pgn-reader/Options.cpp
    ../pgn-reader/main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions(-Wall -Wextra -pedantic -pedantic-errors -fexceptions)
    if (CODE_COVERAGE)
        add_definitions (-O0)
    else()
        add_definitions (-O3)
    endif()

    set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )
endif ()

add_executable(pgn-reader-with-meteor-chess ${pgn_reader_with_meteor_chess_sources})

# find libmongo-client
find_package(PkgConfig)
pkg_search_module (LibMongoClient REQUIRED libmongo-client)
if (LibMongoClient_FOUND)
  include_directories(${LibMongoClient_INCLUDE_DIRS})
  target_link_libraries (pgn-reader-with-meteor-chess ${LibMongoClient_LIBRARIES})
  if (ENABLE_STATIC_LINKING)
    target_link_libraries (pgn-reader-with-meteor-chess glib-2.0 pcre pthread m)
  endif (ENABLE_STATIC_LINKING)
else ()
  message ( FATAL_ERROR "libmongo-client was not found!" )
endif (LibMongoClient_FOUND)


# # # tests for pgn-reader-with-meteor-chess # # #

# different invocations for help
add_test(NAME pgn-reader-with-mc-help-default
         COMMAND $<TARGET_FILE:pgn-reader-with-meteor-chess> --help)
add_test(NAME pgn-reader-with-mc-help-question-mark
         COMMAND $<TARGET_FILE:pgn-reader-with-meteor-chess> -?)
add_test(NAME pgn-reader-with-mc-help-windows-style
         COMMAND $<TARGET_FILE:pgn-reader-with-meteor-chess> /?)

# version information
add_test(NAME pgn-reader-with-mc-version
         COMMAND $<TARGET_FILE:pgn-reader-with-meteor-chess> --version)

# test run with example PGN file, 1 ms delay (to keep test fast)
add_test(NAME pgn-reader-with-mc-steinitz
         COMMAND $<TARGET_FILE:pgn-reader-with-meteor-chess> --pgn ${CMAKE_CURRENT_SOURCE_DIR}/../pgn-reader/examples/steinitz1887.pgn --delay 1)
