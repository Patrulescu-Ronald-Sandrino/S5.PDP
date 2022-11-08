//
// Created by kamui on 07.11.2022.
//

#ifndef HOMEWORK3_MATRIX_H
#define HOMEWORK3_MATRIX_H

#include <stdexcept>
#include <ostream>
#include "../util/Random.h"

using namespace std;

struct Matrix {
private:
    size_t m_size;
    int** m_data;
public:
    //region basics
    explicit Matrix(size_t mSize) : m_size(mSize), m_data(new int*[m_size]) {
        auto random = Random(100);
        for (int i = 0; i < m_size; ++i) {
            m_data[i] = new int[m_size];
            for (int j = 0; j < m_size; ++j) {
                m_data[i][j] = (int) random();
            }
        }
    }

    Matrix(const Matrix& other) : m_size(other.m_size), m_data(new int*[m_size]) {
        if (m_size != other.m_size)
            throw runtime_error("Size must be equal.");

        for (int i = 0; i < m_size; ++i) {
            m_data[i] = new int[m_size];
            for (int j = 0; j < m_size; ++j) {
                m_data[i][j] = other.m_data[i][j];
            }
        }
    }

    Matrix& operator=(const Matrix& other) {
        if (this == &other)
            return *this;

        if (m_size != other.m_size)
            throw runtime_error("Size must be equal.");

        for (int i = 0; i < m_size; ++i) {
            for (int j = 0; j < m_size; ++j) {
                m_data[i][j] = other.m_data[i][j];
            }
        }

        return *this;
    }

    ~Matrix() {
        for (int i = 0; i < m_size; ++i) {
            delete[] m_data[i];
        }
        delete[] m_data;
    }

    friend ostream &operator<<(ostream &os, const Matrix &matrix) {
        os << "Matrix{" << endl;
        os << "size=" << matrix.m_size << "," << endl;
        os << "data=" << endl;
        for (int i = 0; i < matrix.m_size; ++i) {
            for (int j = 0; j < matrix.m_size; ++j) {
                os << matrix.m_data[i][j] << " ";
            }
            os << endl;
        }
        os << "}" << endl;

        return os;
    }

    size_t size() const {
        return m_size;
    }

    size_t area() const {
        return m_size * m_size;
    }

    void set(size_t row, size_t column, int value) {
        auto inRange = [](size_t x, size_t min, size_t max) {
            return x >= min && x <= max;
        };

        if (!inRange(row, 0, m_size - 1) || !inRange(column, 0, m_size - 1))
            throw runtime_error("Index out of range.");

        m_data[row][column] = value;
    }

    int computeProductAt(int row, int column, const Matrix& other) {
        if (m_size != other.m_size)
            throw runtime_error("Size must be equal.");

        auto inRange = [](size_t x, size_t min, size_t max) {
            return x >= min && x <= max;
        };

        if (!inRange(row, 0, m_size - 1) || !inRange(column, 0, m_size - 1))
            throw runtime_error("Index out of range.");

        auto result = 0;
        for (int i = 0; i < m_size; ++i) {
            result += m_data[row][i] * other.m_data[i][column];
        }

        return result;
    }
    //endregion
};


#endif //HOMEWORK3_MATRIX_H
