//
// Created by kamui on 08.11.2022.
//

#ifndef HOMEWORK3_KTHTASK_H
#define HOMEWORK3_KTHTASK_H


#include "MatrixTask.h"

using namespace std;

class KthTask: public MatrixTask {
private:
    size_t startRow;
    size_t startColumn;
    size_t count;
    int k;
public:
    KthTask(Matrix &factorMatrix1, Matrix &factorMatrix2, Matrix &resultMatrix, size_t startRow, size_t startColumn,
            size_t count, int k) : MatrixTask(factorMatrix1, factorMatrix2, resultMatrix), startRow(startRow),
                                   startColumn(startColumn), count(count), k(k) {

    }

    vector<pair<int, int>> computePositions() override {

    }
};


#endif HOMEWORK3_KTHTASK_H
