//
// Created by kamui on 08.11.2022.
//

#ifndef HOMEWORK3_ROWSTRATEGY_H
#define HOMEWORK3_ROWSTRATEGY_H


#include "GenerationStrategy.h"
#include "../matrix_task/RowTask.h"

class RowStrategy : public GenerationStrategy {
public:
    function<void()> createTask(int threadIdx, int numberOfThreads, Matrix factorMatrix1, Matrix factorMatrix2,
                                Matrix resultMatrix) const override {
        const size_t matrixArea = resultMatrix.area();
        size_t count = matrixArea / numberOfThreads;

        size_t startRow = threadIdx * count / resultMatrix.size();
        size_t startColumn = threadIdx * count % resultMatrix.size();

        if (threadIdx == numberOfThreads - 1) {
            count += matrixArea % numberOfThreads;
        }

        return [&factorMatrix1, &factorMatrix2, &resultMatrix, startRow, startColumn, count](){
            RowTask(factorMatrix1, factorMatrix2, resultMatrix, startRow, startColumn, count).run();
        };
    }
};


#endif //HOMEWORK3_ROWSTRATEGY_H
