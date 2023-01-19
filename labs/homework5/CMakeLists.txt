cmake_minimum_required(VERSION 3.24)
project(homework5)

set(CMAKE_CXX_STANDARD 20)

add_executable(homework5 main.cpp ../homework7/model/Polynomial.h ../homework7/Util.h domain/choices.h domain/algorithms/Algorithm.h)
