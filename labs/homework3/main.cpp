#include <iostream>
#include "Matrix.h"


/*
 class ThreadsApproach {
     factorMatrix1
     factorMatrix2
     resultMatrix => get/set
     numberOfThreads
     generationStrategy
}
 */

int main() {
    Matrix m = Matrix(2);

    cout << m;
    /*
    ThreadsApproach threadsApproach = ManualThreadsApproach(numberOfThreads, generationStrategy);
    auto start = std::chrono::high_resolution_clock::now();
    Matrix result = threadsApproach.run();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;
    cout << result;
     */

    return 0;
}
