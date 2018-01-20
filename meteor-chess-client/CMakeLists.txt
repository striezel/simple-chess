# We might support earlier versions, too, but it's only tested with 3.0.2.
cmake_minimum_required (VERSION 3.0)

project(meteor-chess-client)

set(meteor-chess-client_sources
    ../data/Board.cpp
    ../data/Castling.cpp
    ../data/Field.cpp
    ../data/Piece.cpp
    ../db/mongo/Convert.cpp
    ../db/mongo/IdGenerator.cpp
    ../db/mongo/libmongoclient/BSON.cpp
    ../db/mongo/libmongoclient/Connection.cpp
    ../db/mongo/libmongoclient/QueryCursor.cpp
    ../db/mongo/libmongoclient/Server.cpp
    ../evaluation/CheckEvaluator.cpp
    ../evaluation/CompoundEvaluator.cpp
    ../evaluation/MaterialEvaluator.cpp
    ../evaluation/MobilityEvaluator.cpp
    ../evaluation/PromotionEvaluator.cpp
    ../rules/check.cpp
    ../rules/Moves.cpp
    ../search/Node.cpp
    ../search/Search.cpp
    ../util/GitInfos.cpp
    ../util/strings.cpp
    Options.cpp
    main.cpp)

add_definitions(-std=c++0x)
if (CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-Wall -O3 -fexceptions -std=c++11)
endif (CMAKE_COMPILER_IS_GNUCC)

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(meteor-chess-client ${meteor-chess-client_sources})

# find libmongo-client
find_package(PkgConfig)
pkg_search_module (LibMongoClient REQUIRED libmongo-client)
if (LibMongoClient_FOUND)
  include_directories(${LibMongoClient_INCLUDE_DIRS})
  target_link_libraries (meteor-chess-client ${LibMongoClient_LIBRARIES})
else ()
  message ( FATAL_ERROR "libmongo-client was not found!" )
endif (LibMongoClient_FOUND)


### tests for meteor-chess-client ###

# different invocations for help
add_test(NAME meteor-chess-client-help-default
         COMMAND $<TARGET_FILE:meteor-chess-client> --help)
add_test(NAME meteor-chess-lient-help-question-mark
         COMMAND $<TARGET_FILE:meteor-chess-client> -?)
add_test(NAME meteor-chess-client-help-windows-style
         COMMAND $<TARGET_FILE:meteor-chess-client> /?)

# version information
add_test(NAME meteor-chess-client-version
         COMMAND $<TARGET_FILE:meteor-chess-client> --version)
