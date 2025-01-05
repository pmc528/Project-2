cmake_minimum_required(VERSION 3.3)
project(DijkstrasShortestPath)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp nodedata.cpp nodedata.h graphm.cpp graphm.h graphl.cpp graphl.h)
add_executable(DijkstrasShortestPath ${SOURCE_FILES})