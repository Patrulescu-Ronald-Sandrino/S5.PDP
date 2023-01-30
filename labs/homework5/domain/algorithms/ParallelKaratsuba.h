//
// Created by kamui on 23.12.2022.
//

#ifndef HOMEWORK5_PARALLELKARATSUBA_H
#define HOMEWORK5_PARALLELKARATSUBA_H


#include <future>
#include "Algorithm.h"
#include "SequentialKaratsuba.h"

class ParallelKaratsuba : public Algorithm {
public:
    Polynomial multiply(const Polynomial &p1, const Polynomial &p2) override {
        return multiply(p1, p2, 0);
    }

    Polynomial multiply(const Polynomial &p1, const Polynomial &p2, int depth) {
        if (depth > MAX_DEPTH or (p1.getDegree() < 2 or p2.getDegree() < 2)) {
            return SequentialKaratsuba().multiply(p1, p2);
        }

        int len = max(p1.getDegree(), p2.getDegree()) / 2;

        Polynomial p1Low = p1.low(len);
        Polynomial p1High = p1.high(len);
        Polynomial p2Low = p2.low(len);
        Polynomial p2High = p2.high(len);

        auto future1 = multiplyAsync(p1High, p2High, depth + 1);
        auto future2 = multiplyAsync(p1Low + p1High, p2Low + p2High, depth + 1);
        auto future3 = multiplyAsync(p1Low, p2Low, depth + 1);

        auto production1 = future1.get();
        auto production2 = future2.get();
        auto production3 = future3.get();

        auto term1 = production1 << (2 * len);
        auto term2 = (production2 - production1 - production3) << len;
        auto& term3 = production3;

        return term1 + term2 + term3;
    }

private:
    static const int MAX_DEPTH = 4;

    future<Polynomial> multiplyAsync(const Polynomial& p1, const Polynomial &p2, int depth) {
        return async(launch::async, [this, p1, p2, depth] { return multiply(p1, p2, depth + 1); });
    }
};


#endif //HOMEWORK5_PARALLELKARATSUBA_H
