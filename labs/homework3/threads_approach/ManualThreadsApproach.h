//
// Created by kamui on 08.11.2022.
//

#ifndef HOMEWORK3_MANUALTHREADSAPPROACH_H
#define HOMEWORK3_MANUALTHREADSAPPROACH_H


#include <thread>
#include "ThreadsApproach.h"
#include "../matrix_task/MatrixTask.h"

class ManualThreadsApproach : public ThreadsApproach {
private:
    vector<thread> threads;

public:
    ManualThreadsApproach(size_t matrixSize, int numberOfThreads, const MatrixTask& generationStrategy)
            : ThreadsApproach(matrixSize, numberOfThreads, generationStrategy) {
        threads.reserve(numberOfThreads);
    }

    void threadsCleanup() override {
        for (auto& thread : threads) {
            thread.join();
        }
    }
};

class ManualThreadsApproachFactory : public ThreadsApproachFactory {
public:
    unique_ptr<ThreadsApproach> createThreadsApproach(size_t matrixSize, int numberOfThreads, const MatrixTask& generationStrategy) override {
        return make_unique<ManualThreadsApproach>(matrixSize, numberOfThreads, generationStrategy);
    }
};


#endif //HOMEWORK3_MANUALTHREADSAPPROACH_H
