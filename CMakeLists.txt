cmake_minimum_required(VERSION 3.7)
project(ctci)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp big_o.cpp chapter_01.cpp)
add_executable(ctci ${SOURCE_FILES})