cmake_minimum_required (VERSION 3.8)

include (CheckIncludeFileCXX)
check_include_file_cxx (catch2/catch_test_macros.hpp HAS_CATCH_V3_HEADER)
check_include_file_cxx (catch2/catch.hpp HAS_CATCH_V2_HEADER)

if (HAS_CATCH_V3_HEADER AND NOT HAS_CATCH_V2_HEADER)
  set(HAS_CATCH_V3 ON)
else ()
  set(HAS_CATCH_V3 OFF)
endif ()

# Recurse into subdirectory for app tests.
add_subdirectory (apps)

# Recurse into subdirectory for library tests.
add_subdirectory (library)

# Recurse into subdirectory for engine tests.
add_subdirectory (engine)
