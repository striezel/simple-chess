# We might support earlier versions, too, but try to use a more recent one.
cmake_minimum_required (VERSION 3.8)

# Recurse into subdirectory for library tests.
add_subdirectory (library)

# Recurse into subdirectory for engine tests.
add_subdirectory (engine)
