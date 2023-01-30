#include <iostream>
#include <chrono>
#include "threads_approach/ManualThreadsApproach.h"
#include "threads_approach/ThreadPoolThreadsApproach.h"
#include "generation_strategy/GenerationStrategy.h"
#include "generation_strategy/RowStrategy.h"
#include "generation_strategy/ColumnStrategy.h"
#include "generation_strategy/KthStrategy.h"


pair<long, Matrix> runThreadsApproach(ThreadsApproachFactory& threadsApproachFactory, size_t matrixSize, int numberOfThreads, const GenerationStrategy& generationStrategy) {
    auto threadsApproach = threadsApproachFactory.createThreadsApproach(matrixSize, numberOfThreads, generationStrategy);

    auto start = chrono::high_resolution_clock::now();
    auto result = threadsApproach->run();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    return make_pair(duration, result);
}


int main() {
    // --------------------- play with these values ---------------------
    size_t iterations = 10;
    size_t matrixSize = 2000;
    int numberOfThreads = 10;
    GenerationStrategy* generationStrategy = new ColumnStrategy(); // RowStrategy(), ColumnStrategy(), KthStrategy()
    auto threadsApproachFactory = ThreadPoolThreadsApproachFactory(); // ManualThreadsApproachFactory(), ThreadPoolThreadsApproachFactory()
    // 1000 iterations
    // 20x20 matrix, 20 threads, row, thread pool - ~65 μs
    // 20x20 matrix, 1 threads, kth, thread pool - ~1 μs
    // 20x20 matrix, 10 threads, kth, thread pool - ~31 μs
    // 20x20 matrix, 10 threads, kth, manual - ~104 μs
    // 20x20 matrix, 1 threads, kth, manual - ~48 μs
    // 20x20 matrix, 10 threads, row, pool - ~44 μs
    // 20x20 matrix, 10 threads, row, manual - ~104 μs
    // 20x20 matrix, 10 threads, column, manual - ~110 μs
    // 20x20 matrix, 10 threads, column, pool - ~42 μs

    // ------------------------------------------------------------------
    long sum = 0;

    for (int i = 0; i < iterations; ++i) {
        auto [duration, resultMatrix] = runThreadsApproach(threadsApproachFactory, matrixSize, numberOfThreads, *generationStrategy);
        sum += duration;
    }

    cout << "Time taken by function: " << sum / iterations << " μs" << endl;

    delete generationStrategy;

    return 0;
}
