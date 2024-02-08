cmake_minimum_required (VERSION 3.8)

# tests for parameter misuse
add_test(NAME pgn-reader_parameter_misuse
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/parameter-misuse.sh $<TARGET_FILE:pgn-reader>)

if (NOT WIN32 AND NOT NO_METEOR_CHESS)
  add_test(NAME pgn-reader-with-mc_parameter_misuse
           COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/parameter-misuse-with-meteor.sh $<TARGET_FILE:pgn-reader-with-meteor-chess>)
endif ()
