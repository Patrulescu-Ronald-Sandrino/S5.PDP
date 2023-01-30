cmake_minimum_required(VERSION 3.24)
project(homework6)

set(CMAKE_CXX_STANDARD 20)

add_executable(homework6 main.cpp Graph.h util.h GraphProvider.h HamiltonianCycleFinder.h Driver.h)
