cmake_minimum_required (VERSION 3.8)

# tests for parameter misuse
add_test(NAME meteor-chess-client_parameter_misuse
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/parameter-misuse.sh $<TARGET_FILE:meteor-chess-client>)
