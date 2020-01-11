# We might support earlier versions, too, but those have not been tested.
cmake_minimum_required (VERSION 2.8)

enable_testing()

# Recurse into subdirectory for simple-chess-cli.
add_subdirectory (simple-chess-cli)

# Recurse into subdirectory for pgn-reader.
add_subdirectory (pgn-reader)

# Recurse into subdirectory for pgn-reader with meteor-chess support.
add_subdirectory (pgn-reader-with-meteor-chess)

# Recurse into subdirectory for engine.
add_subdirectory (engine)

# Recurse into subdirectory for meteor-chess-client.
add_subdirectory (meteor-chess-client)

# Recurse into subdirectory for competing-evaluators.
add_subdirectory (competing-evaluators)

# Recurse into subdirectory for tests.
add_subdirectory (tests)
