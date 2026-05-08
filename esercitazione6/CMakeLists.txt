cmake_minimum_required(VERSION 3.20)
project(esercitazione6) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla -Wno-sign-compare")

## Creo i target per l' eseguibile che effettuerà il test
add_executable(test_graph test_graph.cpp)
add_test(NAME testgraph COMMAND test_graph)


enable_testing()