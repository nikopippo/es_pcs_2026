cmake_minimum_required(VERSION 3.10)

project(esercitazione3)

set(CMAKE_CXX_STANDARD 20)				# necessario per template nella classe rational
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")