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
    size_t iterations = 1000;
    size_t matrixSize = 20;
    int numberOfThreads = 20;
    GenerationStrategy* generationStrategy = new RowStrategy();
    auto threadsApproachFactory = ThreadPoolThreadsApproachFactory();
    // 1000 iterations
    // 20x20 matrix, 20 threads, row strategy, thread pool - ~65 μs
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
