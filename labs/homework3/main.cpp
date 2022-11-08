#include <iostream>
#include <chrono>
#include "domain/Matrix.h"
#include "matrix_task/MatrixTask.h"
#include "matrix_task/RowTask.h"
#include "threads_approach/ManualThreadsApproach.h"


int main() {
    // --------------------- play with these values ---------------------
    size_t matrixSize = 9;
    int numberOfThreads = 3;
    MatrixTask generationStrategy = RowTask();
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
