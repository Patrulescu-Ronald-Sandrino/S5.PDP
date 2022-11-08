//
// Created by kamui on 08.11.2022.
//

#ifndef HOMEWORK3_THREADPOOLTHREADSAPPROACH_H
#define HOMEWORK3_THREADPOOLTHREADSAPPROACH_H


#include <memory>
#include "ThreadsApproach.h"

class ThreadPoolThreadsApproach : public ThreadsApproach {
public:
    ThreadPoolThreadsApproach(size_t matrixSize, int numberOfThreads, const MatrixTask& generationStrategy)
            : ThreadsApproach(matrixSize, numberOfThreads, generationStrategy) {}

    void threadsCleanup() override {
    }
};

class ThreadPoolThreadsApproachFactory : public ThreadsApproachFactory {
public:
    unique_ptr<ThreadsApproach> createThreadsApproach(size_t matrixSize, int numberOfThreads, const MatrixTask& generationStrategy) override {
        return make_unique<ThreadPoolThreadsApproach>(matrixSize, numberOfThreads, generationStrategy);
    }
};

#endif //HOMEWORK3_THREADPOOLTHREADSAPPROACH_H
