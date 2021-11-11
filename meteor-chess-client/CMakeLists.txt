# We might support earlier versions, too, but try to use a more recent one.
cmake_minimum_required (VERSION 3.8)

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
    Options.cpp
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

# version information in JSON format
add_test(NAME meteor-chess-client-version-json
         COMMAND $<TARGET_FILE:meteor-chess-client> --version --json)
