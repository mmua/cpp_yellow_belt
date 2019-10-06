cmake_minimum_required(VERSION 3.14)
project(cpp_yellow_belt)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_yellow_belt main.cpp date.h date.cpp database.h token.h token.cpp condition_parser.h condition_parser.cpp condition_parser_test.cpp node.h database.cpp)