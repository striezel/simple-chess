# We might support earlier versions, too, but it's only tested with 3.0.2.
cmake_minimum_required (VERSION 3.0)

project(pgn-reader-with-meteor-chess)

set(pgn_reader_with_meteor_chess_sources
    ../algorithm/Apply.cpp
    ../data/Board.cpp
    ../data/Castling.cpp
    ../data/Field.cpp
    ../data/ForsythEdwardsNotation.cpp
    ../data/HalfMove.cpp
    ../data/Piece.cpp
    ../data/PortableGameNotation.cpp
    ../data/Result.cpp
    ../db/mongo/Convert.cpp
    ../db/mongo/IdGenerator.cpp
    ../db/mongo/libmongoclient/BSON.cpp
    ../db/mongo/libmongoclient/Connection.cpp
    ../db/mongo/libmongoclient/QueryCursor.cpp
    ../db/mongo/libmongoclient/Server.cpp
    ../pgn/Parser.cpp
    ../pgn/ParserException.cpp
    ../pgn/Token.cpp
    ../pgn/Tokenizer.cpp
    ../pgn/UnconsumedTokensException.cpp
    ../rules/check.cpp
    ../rules/Moves.cpp
    ../ui/Console.cpp
    ../util/strings.cpp
    ../pgn-reader/Options.cpp
    ../pgn-reader/main.cpp)

add_definitions(-std=c++0x)
if (CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-Wall -O3 -fexceptions -std=c++11)
endif (CMAKE_COMPILER_IS_GNUCC)

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(pgn-reader-with-meteor-chess ${pgn_reader_with_meteor_chess_sources})

# find libmongo-client
find_package(PkgConfig)
pkg_search_module (LibMongoClient REQUIRED libmongo-client)
if (LibMongoClient_FOUND)
  include_directories(${LibMongoClient_INCLUDE_DIRS})
  target_link_libraries (pgn-reader-with-meteor-chess ${LibMongoClient_LIBRARIES})
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
