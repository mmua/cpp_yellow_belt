cmake_minimum_required(VERSION 3.14)
project(cpp_yellow_belt)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_yellow_belt main.cpp query.h query.cpp responses.h responses.cpp bus_manager.h bus_manager.cpp)
