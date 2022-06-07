# We might support earlier versions, too, but try to use a more recent one.
cmake_minimum_required (VERSION 3.8)

project(simple-chess)

enable_testing()

# option for code coverage
option(CODE_COVERAGE "Build with code coverage (GCC only)" OFF)
# If CODE_COVERAGE is on (e. g. via `cmake -DCODE_COVERAGE=ON`), then all
# binaries are built with code coverage. The option is off by default.
# Currently this only works with GCC.
if (CODE_COVERAGE)
  if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR "Code coverage builds need GCC compiler!")
  endif ()
  # set coverage options for GCC
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
endif ()

# Recurse into subdirectory for simple-chess-cli.
add_subdirectory (simple-chess-cli)

# Recurse into subdirectory for pgn-reader.
add_subdirectory (pgn-reader)

if (NOT WIN32)
  # Recurse into subdirectory for pgn-reader with meteor-chess support.
  add_subdirectory (pgn-reader-with-meteor-chess)
endif (NOT WIN32)

# Recurse into subdirectory for engine.
add_subdirectory (engine)

if (NOT WIN32)
  # Recurse into subdirectory for meteor-chess-client.
  add_subdirectory (meteor-chess-client)
endif (NOT WIN32)

# Recurse into subdirectory for competing-evaluators.
add_subdirectory (competing-evaluators)

# Recurse into subdirectory for speedbench.
add_subdirectory (speedbench)

if (NOT MSVC)
  # Recurse into subdirectory for tests.
  add_subdirectory (tests)
endif (NOT MSVC)
