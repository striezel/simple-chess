# We might support earlier versions, too, but that has not been tested yet.
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
    ../../data/Result.cpp
    ../../evaluation/CastlingEvaluator.cpp
    ../../evaluation/CheckEvaluator.cpp
    ../../evaluation/CompoundCreator.cpp
    ../../evaluation/CompoundEvaluator.cpp
    ../../evaluation/LinearMobilityEvaluator.cpp
    ../../evaluation/MaterialEvaluator.cpp
    ../../evaluation/PromotionEvaluator.cpp
    ../../evaluation/RootMobilityEvaluator.cpp
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
    evaluation/testsCastlingEvaluator.cpp
    evaluation/testsCheckEvaluator.cpp
    evaluation/testsCompoundCreator.cpp
    evaluation/testsCompoundEvaluator.cpp
    evaluation/testsLinearMobilityEvaluator.cpp
    evaluation/testsMaterialEvaluator.cpp
    evaluation/testsPromotionEvaluator.cpp
    evaluation/testsRootMobilityEvaluator.cpp
    rules/testsCheck.cpp
    rules/testsMoves.cpp
    search/testsSearch.cpp
    util/testsStrings.cpp
    testsPGN.cpp
    main.cpp)

add_definitions(-std=c++14)
if (CMAKE_COMPILER_IS_GNUCC)
    add_definitions(-Wall -O3 -fexceptions -std=c++14)
endif (CMAKE_COMPILER_IS_GNUCC)

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(simple_chess_tests_catch ${simple_chess_tests_catch_sources})

# add test run
add_test(NAME simple-chess-tests
         COMMAND $<TARGET_FILE:simple_chess_tests_catch>)
