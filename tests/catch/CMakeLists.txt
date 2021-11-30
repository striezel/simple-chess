# We might support earlier versions, too, but try to use a more recent one.
cmake_minimum_required (VERSION 3.8)

project(simple_chess_tests_catch)

set(simple_chess_tests_catch_sources
    ../../libsimple-chess/data/Board.cpp
    ../../libsimple-chess/data/Castling.cpp
    ../../libsimple-chess/data/Field.cpp
    ../../libsimple-chess/data/ForsythEdwardsNotation.cpp
    ../../libsimple-chess/data/HalfMove.cpp
    ../../libsimple-chess/data/Piece.cpp
    ../../libsimple-chess/data/PortableGameNotation.cpp
    ../../libsimple-chess/data/Result.cpp
    ../../libsimple-chess/evaluation/CastlingEvaluator.cpp
    ../../libsimple-chess/evaluation/CheckEvaluator.cpp
    ../../libsimple-chess/evaluation/CompoundCreator.cpp
    ../../libsimple-chess/evaluation/CompoundEvaluator.cpp
    ../../libsimple-chess/evaluation/LinearMobilityEvaluator.cpp
    ../../libsimple-chess/evaluation/MaterialEvaluator.cpp
    ../../libsimple-chess/evaluation/PromotionEvaluator.cpp
    ../../libsimple-chess/evaluation/RootMobilityEvaluator.cpp
    ../../libsimple-chess/pgn/Parser.cpp
    ../../libsimple-chess/pgn/ParserException.cpp
    ../../libsimple-chess/pgn/Token.cpp
    ../../libsimple-chess/pgn/Tokenizer.cpp
    ../../libsimple-chess/pgn/UnconsumedTokensException.cpp
    ../../libsimple-chess/rules/check.cpp
    ../../libsimple-chess/rules/Moves.cpp
    ../../libsimple-chess/search/Node.cpp
    ../../libsimple-chess/search/Search.cpp
    ../../util/strings.cpp
    data/testsBoard.cpp
    data/testsCastling.cpp
    data/testsField.cpp
    data/testsForsythEdwardsNotation.cpp
    data/testsHalfMove.cpp
    data/testsPiece.cpp
    data/testsResult.cpp
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

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions(-Wall -fexceptions)
    if (CODE_COVERAGE)
        add_definitions (-O0)
    else()
        add_definitions (-O3)
    endif()
endif ()

set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )

add_executable(simple_chess_tests_catch ${simple_chess_tests_catch_sources})

# add test run
add_test(NAME simple-chess-tests
         COMMAND $<TARGET_FILE:simple_chess_tests_catch>)
