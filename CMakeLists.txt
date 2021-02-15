cmake_minimum_required(VERSION 3.10)
project(network-interfaces)

set(CMAKE_CXX_STANDARD 17)

# set warning level high
if(CMAKE_COMPILER_IS_GNUCC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")
endif()

set(ACS_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CUSTOM_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Git submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
        # Update submodules as needed
        option(GIT_SUBMODULE "Check submodules during build" ON)
        if(GIT_SUBMODULE)
                message(STATUS "Submodule update")
                execute_process(
                        COMMAND ${GIT_EXECUTABLE} submodule update --init
                                --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT
                )
                if(NOT
                   GIT_SUBMOD_RESULT
                   EQUAL
                   "0"
                )
                        message(
                                FATAL_ERROR
                                        "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules"
                        )
                endif()
        endif()
endif()

# GoogleTest
option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
        add_subdirectory(googletest)

        mark_as_advanced(
                BUILD_GMOCK
                BUILD_GTEST
                BUILD_SHARED_LIBS
                gmock_build_tests
                gtest_build_samples
                gtest_build_tests
                gtest_disable_pthreads
                gtest_force_shared_crt
                gtest_hide_internal_symbols
        )

        set_target_properties(gtest PROPERTIES FOLDER extern)
        set_target_properties(gtest_main PROPERTIES FOLDER extern)
        set_target_properties(gmock PROPERTIES FOLDER extern)
        set_target_properties(gmock_main PROPERTIES FOLDER extern)

        enable_testing()
        include(GoogleTest)
        add_subdirectory(unittest)
endif()

add_subdirectory(src)
