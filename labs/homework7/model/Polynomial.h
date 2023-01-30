//
// Created by kamui on 09.12.2022.
//

#ifndef HOMEWORK5_POLYNOMIAL_H
#define HOMEWORK5_POLYNOMIAL_H

#include <vector>
#include <ostream>
#include <iostream>
#include <sstream>
#include "../../homework7/Util.h"

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
    explicit Polynomial(int size, bool random = true) : Polynomial(size - 1,
                                                                     random ? Util::randomIntegers(size, 0, 10)
                                                                            : Util::vectorFromIndexMapping(size)
    ) {}

    explicit Polynomial(const vector<int> &coefficients) : Polynomial(coefficients.size() - 1, coefficients) {}


    /// degree = size - 1
    int getDegree() const {
        return degree;
    }

    const vector<int> &getCoefficients() const {
        return coefficients;
    }

    /// number of coefficients = degree + 1
    int getSize() const {
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
        Polynomial result(newDegree + 1, false);

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
        Polynomial result(newDegree + 1, false);

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

        return {degree + 1 + shift, newCoefficients};
    }

    /*
        public static Polynomial multiplySequence(Polynomial p1, Polynomial p2, int start, int end) {
            Polynomial result = new Polynomial(2 * p1.getDegree() + 1);

            for (int i = start; i < end; i++) {
                for (int j = 0; j < p2.getCoefficients().size(); j++) {
                    result.getCoefficients().set(i + j, result.getCoefficients().get(i + j) + p1.getCoefficients().get(i) * p2.getCoefficients().get(j));
                }
            }

            return result;
        }
    */
    Polynomial multiplySequence(const Polynomial &p2, int start, int end) const {
        Polynomial result(2 * degree + 1, false);

        for (int i = start; i < end; i++) {
            for (int j = 0; j < p2.coefficients.size(); j++) {
                result.coefficients[i + j] += coefficients[i] * p2.coefficients[j];
            }
        }

        return result;
    }
};


#endif //HOMEWORK5_POLYNOMIAL_H
