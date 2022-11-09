//
// Created by kamui on 08.11.2022.
//

#ifndef HOMEWORK3_KTHSTRATEGY_H
#define HOMEWORK3_KTHSTRATEGY_H


#include "GenerationStrategy.h"
#include "../matrix_task/KthTask.h"

class KthStrategy : public GenerationStrategy {
public:
    function<void()> createTask(int threadIdx, int numberOfThreads, const Matrix& factorMatrix1, const Matrix& factorMatrix2, Matrix& resultMatrix) const override {
        const size_t matrixArea = resultMatrix.area();
        size_t count = matrixArea / numberOfThreads;

        size_t startRow = threadIdx / resultMatrix.size();
        size_t startColumn = threadIdx % resultMatrix.size();

        if (threadIdx < matrixArea % numberOfThreads) {
            count++;
        }

        return [&](){
            KthTask(factorMatrix1, factorMatrix2, resultMatrix, startRow, startColumn, count, numberOfThreads).run();
        };
    }
};


#endif //HOMEWORK3_KTHSTRATEGY_H
