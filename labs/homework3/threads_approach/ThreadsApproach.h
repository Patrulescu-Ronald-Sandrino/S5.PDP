//
// Created by kamui on 08.11.2022.
//

#ifndef HOMEWORK3_THREADSAPPROACH_H
#define HOMEWORK3_THREADSAPPROACH_H


#include "../domain/Matrix.h"
#include "../matrix_task/MatrixTask.h"

class ThreadsApproach {
protected:
    Matrix factorMatrix1;
    Matrix factorMatrix2;
    Matrix resultMatrix;

    int numberOfThreads;
    const MatrixTask& generationStrategy;
public:
    ThreadsApproach(size_t matrixSize, int numberOfThreads, const MatrixTask &generationStrategy) : numberOfThreads(
            numberOfThreads), generationStrategy(generationStrategy), factorMatrix1(matrixSize), factorMatrix2(matrixSize),
                                                                                                    resultMatrix(
                                                                                                                matrixSize) {}

    Matrix run() {

        for (int threadIdx = 0; threadIdx < numberOfThreads; ++threadIdx) {
            // create and run m_threads
            // add(threadIdx);
        }

        threadsCleanup();

        return {resultMatrix};
    }

    virtual void threadsCleanup() = 0;

    virtual ~ThreadsApproach() = default;
};


class ThreadsApproachFactory {
public:
    virtual ~ThreadsApproachFactory() = default;
    virtual unique_ptr<ThreadsApproach> createThreadsApproach(size_t matrixSize, int numberOfThreads, const MatrixTask& generationStrategy) = 0;
};


#endif //HOMEWORK3_THREADSAPPROACH_H
