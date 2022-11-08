#include <iostream>
#include <chrono>
#include <memory>
#include "domain/Matrix.h"
#include "generation_strategy/GenerationStrategy.h"
#include "generation_strategy/RowGenerationStrategy.h"
#include "threads_approach/ManualThreadsApproach.h"


int main() {
    // --------------------- play with these values ---------------------
    size_t matrixSize = 9;
    int numberOfThreads = 3;
    GenerationStrategy generationStrategy = RowGenerationStrategy();
    auto threadsApproachFactory = ManualThreadsApproachFactory();
    // ------------------------------------------------------------------

    auto start = std::chrono::high_resolution_clock::now();
    Matrix result = threadsApproachFactory.createThreadsApproach(matrixSize, numberOfThreads, generationStrategy)->run();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
    cout << result;

    return 0;
}
