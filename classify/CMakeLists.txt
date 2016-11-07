cmake_minimum_required(VERSION 3.6)
project(companies)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES airbnb/cidr.cpp)
add_executable(companies ${SOURCE_FILES})