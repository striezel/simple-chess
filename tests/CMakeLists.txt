cmake_minimum_required (VERSION 3.8)

# MSYS2 / MinGW uses Catch 3.x.
if (MINGW)
  set(HAS_CATCH_V3 ON)
else ()
  set(HAS_CATCH_V3 OFF)
endif ()

# Recurse into subdirectory for library tests.
add_subdirectory (library)

# Recurse into subdirectory for engine tests.
add_subdirectory (engine)
