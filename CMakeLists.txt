cmake_minimum_required(VERSION 3.1)
project(algo VERSION 0.1 LANGUAGES CXX)

enable_testing()

add_executable(interview "interview.cpp")
target_compile_definitions(interview PUBLIC BUILD_AND_RUN_TESTS)
target_link_libraries(interview GTest::gtest GTest::gmock)
set_property(TARGET interview PROPERTY CXX_STANDARD 17)
add_test(interview interview)

add_subdirectory(thirdparty)
