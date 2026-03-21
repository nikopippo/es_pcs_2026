cmake_minimum_required(VERSION 3.10)

project(esercitazione2)

add_executable(es2_2 es2_2.cpp)
add_executable(bubblesort bubblesort.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")