cmake_minimum_required (VERSION 3.8...3.31)

# tests for parameter misuse
if (NOT WIN32)
  set(EXT "sh")
else ()
  set(EXT "cmd")
endif()

add_test(NAME pgn-reader_parameter_misuse
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/parameter-misuse.${EXT} $<TARGET_FILE:pgn-reader>)

if (NOT WIN32 AND NOT NO_METEOR_CHESS)
  add_test(NAME pgn-reader-with-mc_parameter_misuse
           COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/parameter-misuse-with-meteor.sh $<TARGET_FILE:pgn-reader-with-meteor-chess>)
endif ()
