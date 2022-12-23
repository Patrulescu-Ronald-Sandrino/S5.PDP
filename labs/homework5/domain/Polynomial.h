//
// Created by kamui on 09.12.2022.
//

#ifndef HOMEWORK5_POLYNOMIAL_H
#define HOMEWORK5_POLYNOMIAL_H

#include <vector>
#include <ostream>
#include <iostream>
#include <sstream>
#include "../Util.h"

using namespace std;

// REMINDER!!!:
static int (*zeroMapping)(unsigned int) = [](unsigned int _) { return 0; };

/**
 * @info NUMBER OF COEFFICIENTS = DEGREE + 1
 */
class Polynomial {
private:
    int degree;
    vector<int> coefficients;
public:
    Polynomial(int degree, const vector<int> &coefficients) : degree(degree), coefficients(coefficients) {
        if (degree < 0)
            throw invalid_argument("Degree must be non-negative");
        if (coefficients.size() != degree + 1)
            throw invalid_argument("Degree and coefficients size mismatch");
    }

    // if random is false, then the coefficients are initialized to 0
    explicit Polynomial(int degree, bool random = true) : Polynomial(degree,
                                                                     random ? Util::randomIntegers(degree + 1, 0, 10)
                                                                            : Util::vectorFromIndexMapping(degree + 1)
    ) {}

    explicit Polynomial(const vector<int> &coefficients) : Polynomial(coefficients.size() - 1, coefficients) {}

    int getDegree() const {
        return degree;
    }

    const vector<int> &getCoefficients() const {
        return coefficients;
    }

    int getNumberOfCoefficients() const {
        return degree + 1;
    }

    bool isCoefficientRank(int i) const {
        return i >= 0 && i <= degree;
    }

    int operator[](int index) const {
        return coefficients[index];
    }

    int &operator[](int index) {
        return coefficients[index];
    }

    friend std::ostream &operator<<(std::ostream &os, const Polynomial &polynomial) {
        int lastIndex = polynomial.degree;
        auto termToString = [&polynomial](int i) {
            return Util::ansiEscape(to_string(polynomial.coefficients[i]), "96") + "*x^" + Util::ansiEscape(to_string(i), "93");
        };

        for (int i = 0; i < lastIndex; ++i) {
            os << termToString(i) << " + ";
        }
        os << termToString(lastIndex);

        return os;
    }

    string toString() const {
        stringstream ss;
        ss << *this;
        return ss.str();
    }

    Polynomial low(int len) const {
        return Polynomial(vector<int>(coefficients.begin(), coefficients.begin() + len));
    }

    Polynomial high(int len) const {
        return Polynomial(vector<int>(coefficients.begin() + len, coefficients.end()));
    }

    Polynomial operator+(const Polynomial &rhs) const {
        int newDegree = max(degree, rhs.degree);
        Polynomial result(newDegree, false);

        for (int i = 0; i <= newDegree; ++i) {
            if (this->isCoefficientRank(i))
                result[i] += this->coefficients[i];
            if (rhs.isCoefficientRank(i))
                result[i] += rhs.coefficients[i];
        }

        return result;
    }

    Polynomial operator-(const Polynomial &rhs) const {
        int newDegree = max(degree, rhs.degree);
        Polynomial result(newDegree, false);

        for (int i = 0; i <= newDegree; ++i) {
            if (this->isCoefficientRank(i))
                result[i] += this->coefficients[i];
            if (rhs.isCoefficientRank(i))
                result[i] -= rhs.coefficients[i];
        }

        return result;
    }

    Polynomial operator<<(int shift) const {
        vector<int> newCoefficients(degree + 1 + shift);

        for (int i = 0; i <= degree; ++i) {
            newCoefficients[i + shift] = (*this)[i];
        }

        return {degree + shift, newCoefficients};
    }
};


#endif //HOMEWORK5_POLYNOMIAL_H
