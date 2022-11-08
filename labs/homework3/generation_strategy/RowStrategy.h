//
// Created by kamui on 08.11.2022.
//

#ifndef HOMEWORK3_COLUMNSTRATEGY_H
#define HOMEWORK3_COLUMNSTRATEGY_H


#include "GenerationStrategy.h"

class RowStrategy : public GenerationStrategy {
public:
    function<void()> createTask(int threadIdx, int numberOfThreads, Matrix factorMatrix1, Matrix factorMatrix2,
                                Matrix result) const override {
        // TODO: implement
        return [](){};
    }
};


#endif //HOMEWORK3_COLUMNSTRATEGY_H
