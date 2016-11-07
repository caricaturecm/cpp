cmake_minimum_required(VERSION 3.6)
project(airbnb)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES shortestDistance.cpp)
add_executable(airbnb ${SOURCE_FILES})