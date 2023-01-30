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
    KthTask(const Matrix &factorMatrix1, const Matrix &factorMatrix2, Matrix &resultMatrix, size_t startRow, size_t startColumn,
            size_t count, int k) : MatrixTask(factorMatrix1, factorMatrix2, resultMatrix), startRow(startRow),
                                   startColumn(startColumn), count(count), k(k) {

    }

    vector<pair<int, int>> computePositions() override {
        vector<pair<int, int>> positions;
        positions.reserve(count);
        auto row = startRow;
        auto column = startColumn;
        auto positionsLeftToAdd = count;

        while (positionsLeftToAdd > 0 && row < factorMatrix1.size() && column < factorMatrix2.size()) {
            positions.emplace_back(row, column);
            positionsLeftToAdd--;
            row += (column + k) / factorMatrix1.size();
            column = (column + k) % factorMatrix1.size();
        }

        return positions;
    }
};


#endif //HOMEWORK3_KTHTASK_H
