# We might support earlier versions, too, but it's only tested with 2.8.9.
cmake_minimum_required (VERSION 2.8)

project(simple_chess_tests_catch)

set(simple_chess_tests_catch_sources
    ../../data/Board.cpp
    ../../data/Castling.cpp
    ../../data/Field.cpp
    ../../data/ForsythEdwardsNotation.cpp
    ../../data/HalfMove.cpp
    ../../data/Piece.cpp
    ../../data/PortableGameNotation.cpp
    ../../evaluation/CheckEvaluator.cpp
    ../../evaluation/CompoundEvaluator.cpp
    ../../evaluation/MaterialEvaluator.cpp
    ../../evaluation/MobilityEvaluator.cpp
    ../../evaluation/PromotionEvaluator.cpp
    ../../pgn/Parser.cpp
    ../../pgn/ParserException.cpp
    ../../pgn/Token.cpp
    ../../pgn/Tokenizer.cpp
    ../../pgn/UnconsumedTokensException.cpp
    ../../rules/check.cpp
    ../../rules/Moves.cpp
    ../../search/Node.cpp
    ../../search/Search.cpp
    ../../util/strings.cpp
    data/testsBoard.cpp
    data/testsCastling.cpp
    data/testsField.cpp
    data/testsForsythEdwardsNotation.cpp
    data/testsHalfMove.cpp
    data/testsPiece.cpp
    evaluation/ConstantEvaluator.cpp
    evaluation/testsCheckEvaluator.cpp
    evaluation/testsCompoundEvaluator.cpp
    evaluation/testsMaterialEvaluator.cpp
    evaluation/testsMobilityEvaluator.cpp
    evaluation/testsPromotionEvaluator.cpp
    rules/testsMoves.cpp
    search/testsSearch.cpp
    util/testsStrings.cpp
    testsPGN.cpp
    main.cpp)

add_definitions(-std=c++0x)
if (CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-Wall -O3 -fexceptions -std=c++11)
endif (CMAKE_COMPILER_IS_GNUCC)

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(simple_chess_tests_catch ${simple_chess_tests_catch_sources})

# add test run
add_test(NAME simple-chess-tests
         COMMAND $<TARGET_FILE:simple_chess_tests_catch>)
