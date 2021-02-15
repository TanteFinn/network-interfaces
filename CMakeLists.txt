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

add_subdirectory(src)
