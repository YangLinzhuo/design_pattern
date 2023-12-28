cmake_minimum_required(VERSION 3.22)
project(design_pattern)

set(CMAKE_CXX_STANDARD 20)

include_directories(src/utils/)

add_executable(${PROJECT_NAME} main.cpp)

add_executable(person src/creational/builder/person.cpp)
