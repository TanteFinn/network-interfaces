cmake_minimum_required(VERSION 3.10)
project(${PROJECT_NAME}_Class)

add_executable(
        ${PROJECT_NAME}
        main.cc
        NetworkInterfaces.cc
)

target_include_directories(${PROJECT_NAME} PUBLIC ../include)