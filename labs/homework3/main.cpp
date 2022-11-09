#include <iostream>
#include <chrono>
#include "threads_approach/ManualThreadsApproach.h"
#include "threads_approach/ThreadPoolThreadsApproach.h"
#include "generation_strategy/GenerationStrategy.h"
#include "generation_strategy/RowStrategy.h"
#include "generation_strategy/ColumnStrategy.h"
#include "generation_strategy/KthStrategy.h"


int main() {
    // --------------------- play with these values ---------------------
    size_t matrixSize = 20;
    int numberOfThreads = 20;
    GenerationStrategy* generationStrategy = new RowStrategy();
    auto threadsApproachFactory = ThreadPoolThreadsApproachFactory();
    // 9 3 row manual => ~250μs
    // 9 3 row threadpool => ~250μs
    // 15 10 row manual => μs
    // 15 10 row threadpool => μs
    // ------------------------------------------------------------------

    auto start = std::chrono::high_resolution_clock::now();
    auto result = threadsApproachFactory.createThreadsApproach(matrixSize, numberOfThreads, *generationStrategy)->run();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
//    cout << result;

    delete generationStrategy;

    return 0;
}
