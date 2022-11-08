cmake_minimum_required(VERSION 3.23)
project(homework3)

set(CMAKE_CXX_STANDARD 23)

add_executable(homework3 main.cpp domain/Matrix.h util/Random.h threads_approach/ThreadsApproach.h generation_strategy/GenerationStrategy.h threads_approach/ManualThreadsApproach.h)
