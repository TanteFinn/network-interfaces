cmake_minimum_required(VERSION 3.10)
project(${PROJECT_NAME}_Class)

add_library(
        ${PROJECT_NAME} STATIC
        NetworkInterfacesClass.cc
)

target_include_directories(${PROJECT_NAME} PUBLIC ../include)