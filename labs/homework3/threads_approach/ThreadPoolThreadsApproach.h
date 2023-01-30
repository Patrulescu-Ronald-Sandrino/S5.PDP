//
// Created by kamui on 08.11.2022.
//

#ifndef HOMEWORK3_THREADPOOLTHREADSAPPROACH_H
#define HOMEWORK3_THREADPOOLTHREADSAPPROACH_H


#include <memory>
#include "ThreadsApproach.h"
#include "../util/ThreadPool.h"

class ThreadPoolThreadsApproach : public ThreadsApproach {
private:
    ThreadPool threadPool;
public:
    ThreadPoolThreadsApproach(size_t matrixSize, int numberOfThreads, const GenerationStrategy& generationStrategy)
            : ThreadsApproach(matrixSize, numberOfThreads, generationStrategy), threadPool(numberOfThreads) {}

    void add(int threadIdx, function<void()> task) override {
        threadPool.enqueue(task);
    }

    void threadsCleanup() override {
        threadPool.close();
    }
};

class ThreadPoolThreadsApproachFactory : public ThreadsApproachFactory {
public:
    unique_ptr<ThreadsApproach> createThreadsApproach(size_t matrixSize, int numberOfThreads, const GenerationStrategy& generationStrategy) override {
        return make_unique<ThreadPoolThreadsApproach>(matrixSize, numberOfThreads, generationStrategy);
    }
};

#endif //HOMEWORK3_THREADPOOLTHREADSAPPROACH_H
