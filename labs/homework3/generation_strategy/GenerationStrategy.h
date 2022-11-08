//
// Created by kamui on 08.11.2022.
//

#ifndef HOMEWORK3_GENERATIONSTRATEGY_H
#define HOMEWORK3_GENERATIONSTRATEGY_H

#include <functional>
#include "../domain/Matrix.h"

using namespace std;

class GenerationStrategy {
public:
    virtual function<void()> createTask(int threadIdx, int numberOfThreads, Matrix factorMatrix1, Matrix factorMatrix2, Matrix resultMatrix) const = 0;

    virtual ~GenerationStrategy() = default;
};


#endif //HOMEWORK3_GENERATIONSTRATEGY_H
