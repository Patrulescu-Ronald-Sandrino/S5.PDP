cmake_minimum_required(VERSION 3.24)
project(homework7)

set(CMAKE_CXX_STANDARD 20)

# Add MPI Package to Project
find_package(MPI REQUIRED)

add_executable(homework7 main.cpp)
# Add libraries for code completion and compiling
target_link_libraries(homework7 PUBLIC MPI::MPI_CXX)
