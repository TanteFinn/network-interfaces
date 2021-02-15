cmake_minimum_required(VERSION 3.10)
project(network-interfaces)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak -g -O0")

# set warning level high
if(CMAKE_COMPILER_IS_GNUCC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")
endif()

set(ACS_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CUSTOM_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory(src)

add_executable(
        ${PROJECT_NAME}
        src/main.cc)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_Class)
