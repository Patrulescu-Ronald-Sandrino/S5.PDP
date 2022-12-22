//
// Created by kamui on 16.12.2022.
//

#ifndef HOMEWORK5_SEQUENTIALKARATSUBA_H
#define HOMEWORK5_SEQUENTIALKARATSUBA_H


#include "Algorithm.h"
#include "SequentialClassic.h"

class SequentialKaratsuba : public Algorithm {
public:
    Polynomial multiply(const Polynomial &p1, const Polynomial &p2) override { // TODO
        if (p1.getDegree() < 2 or p2.getDegree() < 2)
            return SequentialClassic().multiply(p1, p2);

        int len = max(p1.getDegree(), p2.getDegree()) / 2;

        Polynomial p1Low = p1.low(len);
        Polynomial p1High = p1.high(len);
        Polynomial p2Low = p2.low(len);
        Polynomial p2High = p2.high(len);

        auto production1 = multiply(p1High, p2High);
        auto production2 = multiply(p1Low + p1High, p2Low + p2High);
        auto production3 = multiply(p1Low, p2Low);

        auto term1 = production1 << (2 * len);
        auto term2 = (production2 - production1 - production3) << len;
        auto& term3 = production3;

        return term1 + term2 + term3;
    }
};


#endif //HOMEWORK5_SEQUENTIALKARATSUBA_H
