cmake_minimum_required(VERSION 3.10)

project(unittest)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/binary/unittest")

set(BINARY ${PROJECT_NAME})

file(
        GLOB_RECURSE TEST_SOURCES
        LIST_DIRECTORIES false
        *.cc
)
list(
        FILTER
        TEST_SOURCES
        EXCLUDE
        REGEX
        ".*/test_adapter/.*"
)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

target_include_directories(${BINARY} PUBLIC include include)

gtest_add_tests(TARGET ${BINARY})

target_link_libraries(
        ${BINARY}
        PUBLIC gtest
        gmock
        gtest_main
        network-interfaces-Class
)

#
# add_executable(${PROJECT_NAME}_example example.cc )
# target_link_libraries(${PROJECT_NAME}_example gtest_main )
