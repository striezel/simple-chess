cmake_minimum_required (VERSION 3.8...3.31)

# Recurse into subdirectory for simple-chess-cli.
add_subdirectory (simple-chess-cli)

# Recurse into subdirectory for pgn-reader.
add_subdirectory (pgn-reader)

if (NOT WIN32 AND NOT NO_METEOR_CHESS)
  # Recurse into subdirectory for pgn-reader with meteor-chess support.
  add_subdirectory (pgn-reader-with-meteor-chess)
endif (NOT WIN32 AND NOT NO_METEOR_CHESS)

# Recurse into subdirectory for engine.
add_subdirectory (engine)

if (NOT WIN32 AND NOT NO_METEOR_CHESS)
  # Recurse into subdirectory for meteor-chess-client.
  add_subdirectory (meteor-chess-client)
endif (NOT WIN32 AND NOT NO_METEOR_CHESS)
