# We might support earlier versions, too, but those have not been tested.
cmake_minimum_required (VERSION 2.8)

# Recurse into subdirectory for simple-chess-cli.
add_subdirectory (simple-chess-cli)

# Recurse into subdirectory for tests.
add_subdirectory (tests)
