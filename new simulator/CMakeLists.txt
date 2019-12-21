cmake_minimum_required(VERSION 3.15)
project(new_simulator)

set(CMAKE_CXX_STANDARD 14)

add_executable(new_simulator main.cpp utils.h utils.cpp master.cpp master.h turtle.cpp turtle.h human.cpp human.h)