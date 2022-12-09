//
// Created by kamui on 09.12.2022.
//

#ifndef HOMEWORK5_POLYNOMIAL_H
#define HOMEWORK5_POLYNOMIAL_H

#include <vector>
#include <ostream>
#include <iostream>
#include "../Util.h"

using namespace std;

class Polynomial {
private:
    unsigned long degree;
    vector<int> coefficients;
public:
    Polynomial(int degree, const vector<int> &coefficients) : degree(degree), coefficients(coefficients) {}

    explicit Polynomial(int degree) : Polynomial(degree, Util::randomIntegers(degree + 1, 0, 100)) {}

    unsigned long getDegree() const {
        return degree;
    }

    const vector<int> &getCoefficients() const {
        return coefficients;
    }

    friend std::ostream &operator<<(std::ostream &os, const Polynomial &polynomial) {
        unsigned long lastIndex = polynomial.degree;
        auto termToString = [&polynomial](unsigned long i) {
            return to_string(polynomial.coefficients[i]) + " * x^" + to_string(i);
        };

        for (int i = 0; i < lastIndex; ++i) {
            os << termToString(i) << " + ";
        }
        os << termToString(lastIndex);

        return os;
    }
private:

};


#endif //HOMEWORK5_POLYNOMIAL_H
