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

add_executable(3sum "3sum.cpp")
target_link_libraries(3sum GTest::gtest GTest::gmock)
set_property(TARGET 3sum PROPERTY CXX_STANDARD 17)
add_test(3sum 3sum)

add_executable(2sum "2sum.cpp")
target_link_libraries(2sum GTest::gtest GTest::gmock)
set_property(TARGET 2sum PROPERTY CXX_STANDARD 17)
add_test(2sum 2sum)

add_executable(2sum_sorted "2sum_sorted.cpp")
target_link_libraries(2sum_sorted GTest::gtest GTest::gmock)
set_property(TARGET 2sum_sorted PROPERTY CXX_STANDARD 17)
add_test(2sum_sorted 2sum_sorted)

add_executable(calendar_double_booking "calendar_double_booking.cpp")
target_link_libraries(calendar_double_booking GTest::gtest GTest::gmock)
set_property(TARGET calendar_double_booking PROPERTY CXX_STANDARD 17)
add_test(calendar_double_booking calendar_double_booking)

add_executable(longest_common_prefix "longest_common_prefix.cpp")
target_link_libraries(longest_common_prefix GTest::gtest GTest::gmock)
set_property(TARGET longest_common_prefix PROPERTY CXX_STANDARD 17)
add_test(longest_common_prefix longest_common_prefix)

add_executable(regex_match "regex_match.cpp")
target_link_libraries(regex_match GTest::gtest GTest::gmock)
set_property(TARGET regex_match PROPERTY CXX_STANDARD 17)
add_test(regex_match regex_match)

add_executable(mirror_reflection "mirror_reflection.cpp")
target_link_libraries(mirror_reflection GTest::gtest GTest::gmock)
set_property(TARGET mirror_reflection PROPERTY CXX_STANDARD 17)
add_test(mirror_reflection mirror_reflection)

add_subdirectory(thirdparty)

