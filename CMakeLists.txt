cmake_minimum_required(VERSION 3.13)
project(Onegin)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(tests)
add_executable(runTests ${TEST_SRC} )

add_executable(Onegin main.cpp Document.cpp Document.h)

