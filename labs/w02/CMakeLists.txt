cmake_minimum_required(VERSION 3.23)
project(w02)

set(CMAKE_CXX_STANDARD 14)

add_executable(w02
        lab1_pdp.cpp)

# cmakelists file copy https://stackoverflow.com/a/42397802/17299754
file(COPY accounts.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})