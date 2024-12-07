cmake_minimum_required (VERSION 3.8...3.31)

# Recurse into subdirectory for simple-chess-engine tests.
add_subdirectory (engine)

if (NOT WIN32 AND NOT NO_METEOR_CHESS)
  # Recurse into subdirectory for meteor-chess-client tests.
  add_subdirectory (meteor-chess-client)
endif ()

# Recurse into subdirectory for pgn-reader tests.
add_subdirectory (pgn-reader)

# Recurse into subdirectory for simple-chess-cli tests.
add_subdirectory (simple-chess-cli)
