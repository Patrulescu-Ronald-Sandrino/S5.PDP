//
// Created by kamui on 08.11.2022.
//

#ifndef HOMEWORK3_COLUMNTASK_H
#define HOMEWORK3_COLUMNTASK_H


#include "MatrixTask.h"

using namespace std;

class ColumnTask: public MatrixTask {
private:
    size_t startRow;
    size_t startColumn;
    size_t count;
public:
    ColumnTask(Matrix &factorMatrix1, Matrix &factorMatrix2, Matrix &resultMatrix, size_t startRow, size_t startColumn,
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
            row++;
            if (row == factorMatrix1.size()) {
                row = 0;
                column++;
            }
        }

        return positions;
    }
};


#endif HOMEWORK3_COLUMNTASK_H
