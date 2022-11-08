//
// Created by kamui on 08.11.2022.
//

#ifndef HOMEWORK3_ROWTASK_H
#define HOMEWORK3_ROWTASK_H


#include "MatrixTask.h"

class RowTask : public MatrixTask {
private:
    size_t startRow;
    size_t startColumn;
    size_t count;
public:
    RowTask(Matrix &factorMatrix1, Matrix &factorMatrix2, Matrix &resultMatrix, size_t startRow, size_t startColumn,
            size_t count) : MatrixTask(factorMatrix1, factorMatrix2, resultMatrix), startRow(startRow),
                            startColumn(startColumn), count(count) {

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
            column++;
            if (column == factorMatrix1.size()) {
                column = 0;
                row++;
            }
        }

        return positions;
    }
};


#endif //HOMEWORK3_ROWTASK_H
