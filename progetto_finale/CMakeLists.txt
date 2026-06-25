cmake_minimum_required(VERSION 3.20)
project(progetto_finale) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla -Wno-sign-compare")

include_directories(${CMAKE_SOURCE_DIR})	#compila libreria eigen

## Creo i target per l' eseguibile che effettuerà il test
add_executable(main main.cpp)



enable_testing()
