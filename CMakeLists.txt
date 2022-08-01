cmake_minimum_required(VERSION 3.1)
project(algo VERSION 0.1 LANGUAGES CXX)

enable_testing()

add_executable(find_median_k_sorted "find_median_k_sorted.cpp")
target_link_libraries(find_median_k_sorted GTest::gtest GTest::gmock)
set_property(TARGET find_median_k_sorted PROPERTY CXX_STANDARD 17)
add_test(find_median_k_sorted find_median_k_sorted)

add_executable(valid_sudoku "valid_sudoku.cpp")
target_link_libraries(valid_sudoku GTest::gtest GTest::gmock)
set_property(TARGET valid_sudoku PROPERTY CXX_STANDARD 17)
add_test(valid_sudoku valid_sudoku)

add_subdirectory(thirdparty)

