//
// Created by kamui on 08.11.2022.
//

#ifndef HOMEWORK3_MANUALTHREADSAPPROACH_H
#define HOMEWORK3_MANUALTHREADSAPPROACH_H


#include "ThreadsApproach.h"
#include "../generation_strategy/GenerationStrategy.h"

class ManualThreadsApproach : public ThreadsApproach {

public:
    ManualThreadsApproach(size_t matrixSize, int numberOfThreads, const GenerationStrategy& generationStrategy)
            : ThreadsApproach(matrixSize, numberOfThreads, generationStrategy) {}
};

class ManualThreadsApproachFactory : public ThreadsApproachFactory {
public:
    unique_ptr<ThreadsApproach> createThreadsApproach(size_t matrixSize, int numberOfThreads, const GenerationStrategy& generationStrategy) override {
        return make_unique<ManualThreadsApproach>(matrixSize, numberOfThreads, generationStrategy);
    }
};


#endif //HOMEWORK3_MANUALTHREADSAPPROACH_H
