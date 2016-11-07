cmake_minimum_required(VERSION 3.6)
project(dropbox)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES A9/huffmanTree.cpp)

add_executable(dropbox ${SOURCE_FILES})