//
// Created by kamui on 08.11.2022.
//

#ifndef HOMEWORK3_THREADSAPPROACH_H
#define HOMEWORK3_THREADSAPPROACH_H


#include "../domain/Matrix.h"
#include "../generation_strategy/GenerationStrategy.h"

class ThreadsApproach {
private:
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
        return {resultMatrix};
    }

    virtual ~ThreadsApproach() = default;
};


class ThreadsApproachFactory {
public:
    virtual ~ThreadsApproachFactory() = default;
    virtual unique_ptr<ThreadsApproach> createThreadsApproach(size_t matrixSize, int numberOfThreads, const GenerationStrategy& generationStrategy) = 0;
};


#endif //HOMEWORK3_THREADSAPPROACH_H
