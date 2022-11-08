//
// Created by kamui on 08.11.2022.
//

#ifndef HOMEWORK3_MATRIXTASK_H
#define HOMEWORK3_MATRIXTASK_H


#include "../domain/Matrix.h"

class MatrixTask {
protected:;
    Matrix& factorMatrix1;
    Matrix& factorMatrix2;
    Matrix& resultMatrix;
public:
    MatrixTask(Matrix &factorMatrix1, Matrix &factorMatrix2, Matrix &resultMatrix) : factorMatrix1(factorMatrix1),
                                                                                     factorMatrix2(factorMatrix2),
                                                                                     resultMatrix(resultMatrix) {

    }

    virtual ~MatrixTask() = default;

    virtual vector<pair<int, int>> computePositions() = 0;

    void run() {
        for (const auto &position: computePositions()) {
            auto row = position.first;
            auto column = position.second;
            auto value = factorMatrix1.computeProductAt(row, column, factorMatrix2);

            resultMatrix.set(row, column, value);
        }
    }
};


#endif //HOMEWORK3_MATRIXTASK_H
