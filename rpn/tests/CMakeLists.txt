cmake_minimum_required(VERSION 3.5)
project(tests VERSION 0.0.1 LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 20)

find_package(Catch2 REQUIRED)

add_executable(
    tests
    unittest_funciones.cpp
    unittest_parenthesis.cpp
    unittest_convertir_postfija.cpp
    unittest_evaluar_postfija.cpp
    unittest_undoredo.cpp

    # test_rpn.cpp
    # test_undoredo.cpp
    ../src/rpn.cpp
    ../src/tokenizer.cpp
    ../src/undoredo.cpp
)
target_include_directories(tests PUBLIC ../include)
target_link_libraries(tests
    PUBLIC
    # ../src/rpn.cpp
    # ../src/undoredo.cpp
    PRIVATE
    Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(tests)

