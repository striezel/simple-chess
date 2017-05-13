# We might support earlier versions, too, but it's only tested with 2.8.9.
cmake_minimum_required (VERSION 2.8)

project(simple_chess_tests)

set(simple_chess_tests_sources
    ../../data/Board.cpp
    ../../data/Castling.cpp
    ../../data/Field.cpp
    ../../data/ForsythEdwardsNotation.cpp
    ../../data/Piece.cpp
    ../../rules/check.cpp
    ../../rules/Moves.cpp
    ../../util/strings.cpp
    main.cpp)

add_definitions(-std=c++0x)
if (CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-Wall -O3 -fexceptions -std=c++11)
endif (CMAKE_COMPILER_IS_GNUCC)

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(simple_chess_tests ${simple_chess_tests_sources})

# boost test library
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package( Boost COMPONENTS unit_test_framework )
if (Boost_FOUND)
  message ( "Boost library was found." )
  message ( "Include directories: ${Boost_INCLUDE_DIRS}" )
  message ( "Libraries: ${Boost_LIBRARIES}" )
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries (simple_chess_tests ${Boost_LIBRARIES})
else ()
  message ( FATAL_ERROR "Boost test library was not found!" )
endif (Boost_FOUND)


