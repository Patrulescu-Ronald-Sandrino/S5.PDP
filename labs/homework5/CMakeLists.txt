cmake_minimum_required(VERSION 3.24)
project(homework5)

set(CMAKE_CXX_STANDARD 20)

add_executable(homework5 main.cpp domain/Polynomial.h Util.h domain/choices.h domain/algorithms/Algorithm.h)
