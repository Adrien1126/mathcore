cmake_minimum_required(VERSION 3.20)
project(mathcore VERSION 1.0 LANGUAGES CXX)

# Standard C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options globales de compilation (propagées à toutes les targets)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# Option pour activer/désactiver les tests
option(BUILD_TESTS "Build unit tests" ON)

if (BUILD_TESTS)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )

    # Empêche GoogleTest de forcer des options qui pollueraient le projet
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(googletest)
endif()

add_library(mathcore_lib
    src/arithmetic.cpp
    src/algebra.cpp
    src/linalg/linalg_vector.cpp
    src/linalg/linalg_matrix.cpp
    src/linalg/linalg_small_matrix.cpp
    src/linalg/linalg_operations.cpp
    src/matrix.cpp
    src/vector.cpp
    src/stats.cpp
)

add_library(mathcore::mathcore ALIAS mathcore_lib)

target_include_directories(mathcore_lib
    PUBLIC
        include
)

add_executable(program src/main.cpp)

target_link_libraries(program
    PRIVATE
        mathcore::mathcore
)

if (BUILD_TESTS)
    enable_testing()

    add_executable(tests
        tests/test_main.cpp
        tests/test_arithmetic.cpp
        tests/test_algebra.cpp
        tests/test_linalg/test_linalg_vector.cpp  
        tests/test_linalg/test_linalg_matrix.cpp  
        tests/test_linalg/test_linalg_small_matrix.cpp   
        tests/test_linalg/test_linalg_operations.cpp 
        tests/test_stats.cpp
    )

    target_link_libraries(tests
        PRIVATE
            mathcore::mathcore
            gtest_main
    )

    add_test(NAME mathcore_tests COMMAND tests)
endif()
