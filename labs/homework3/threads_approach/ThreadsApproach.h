//
// Created by kamui on 08.11.2022.
//

#ifndef HOMEWORK3_THREADSAPPROACH_H
#define HOMEWORK3_THREADSAPPROACH_H


#include <functional>
#include "../domain/Matrix.h"
#include "../generation_strategy/GenerationStrategy.h"

class ThreadsApproach {
protected:
    Matrix factorMatrix1;
    Matrix factorMatrix2;
    Matrix resultMatrix;

    int numberOfThreads;
    const GenerationStrategy& generationStrategy;
public:
    ThreadsApproach(size_t matrixSize, int numberOfThreads, const GenerationStrategy &generationStrategy) : numberOfThreads(
            numberOfThreads), generationStrategy(generationStrategy), factorMatrix1(matrixSize), factorMatrix2(matrixSize),
                                                                                                            resultMatrix(
                                                                                                                matrixSize) {}

    Matrix run() {
        for (int threadIdx = 0; threadIdx < numberOfThreads; ++threadIdx) {
            auto task = generationStrategy.createTask(threadIdx, numberOfThreads, factorMatrix1, factorMatrix2, resultMatrix);
            add(threadIdx, task);
        }

        threadsCleanup();

        return {resultMatrix};
    }
    
    virtual void add(int threadIdx, function<void()> task) = 0;

    virtual void threadsCleanup() = 0;

    virtual ~ThreadsApproach() = default;
};


class ThreadsApproachFactory {
public:
    virtual ~ThreadsApproachFactory() = default;
    virtual unique_ptr<ThreadsApproach> createThreadsApproach(size_t matrixSize, int numberOfThreads, const GenerationStrategy& generationStrategy) = 0;
};


#endif //HOMEWORK3_THREADSAPPROACH_H
