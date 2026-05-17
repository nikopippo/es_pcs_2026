cmake_minimum_required(VERSION 3.20)
project(esercitazione9) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla -Wno-sign-compare")

## Creo i target per l' eseguibile che effettuerà il test
add_executable(test_graph_visit test_graph_visit.cpp)
add_test(NAME testgraphvisit COMMAND test_graph_visit)

add_executable(test_dijkstra test_dijkstra.cpp)
add_test(NAME test_dijkstra COMMAND test_dijkstra)


enable_testing()