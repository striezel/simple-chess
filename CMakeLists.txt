# We might support earlier versions, too, but try to use a more recent one.
cmake_minimum_required (VERSION 3.8)

project(simple-chess)

enable_testing()

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

# Recurse into subdirectory for tests.
add_subdirectory (tests)
