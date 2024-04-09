cmake_minimum_required (VERSION 3.8)

project(simple_chess_tests)

set(simple_chess_tests_sources
    ../../libsimple-chess/data/Board.cpp
    ../../libsimple-chess/data/Castling.cpp
    ../../libsimple-chess/data/Field.cpp
    ../../libsimple-chess/data/ForsythEdwardsNotation.cpp
    ../../libsimple-chess/data/HalfMove.cpp
    ../../libsimple-chess/data/Piece.cpp
    ../../libsimple-chess/data/PortableGameNotation.cpp
    ../../libsimple-chess/data/Result.cpp
    ../../libsimple-chess/db/mongo/Convert.cpp
    ../../libsimple-chess/db/mongo/IdGenerator.cpp
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
    ../../libsimple-chess/ui/letters.hpp
    ../../libsimple-chess/ui/symbols.hpp
    ../../util/strings.cpp
    data/Board.cpp
    data/Castling.cpp
    data/Field.cpp
    data/ForsythEdwardsNotation.cpp
    data/HalfMove.cpp
    data/Piece.cpp
    data/Result.cpp
    db/mongo/Convert.cpp
    db/mongo/IdGenerator.cpp
    evaluation/ConstantEvaluator.cpp
    evaluation/CastlingEvaluator.cpp
    evaluation/CheckEvaluator.cpp
    evaluation/CompoundCreator.cpp
    evaluation/CompoundEvaluator.cpp
    evaluation/LinearMobilityEvaluator.cpp
    evaluation/MaterialEvaluator.cpp
    evaluation/PromotionEvaluator.cpp
    evaluation/RootMobilityEvaluator.cpp
    rules/Check.cpp
    rules/Moves.cpp
    search/Search.cpp
    ui/letters.cpp
    ui/symbols.cpp
    util/Strings.cpp
    PGN.cpp
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

    set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )
endif ()

add_executable(simple_chess_tests ${simple_chess_tests_sources})

# MSYS2 / MinGW uses Catch 3.x.
if (HAS_CATCH_V3)
    find_package(Catch2 3 REQUIRED)
    target_link_libraries(simple_chess_tests Catch2::Catch2WithMain)
endif ()

# add test run
add_test(NAME simple-chess-tests
         COMMAND $<TARGET_FILE:simple_chess_tests>)
