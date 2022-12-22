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
//        if (p1.getDegree() < 2 or p2.getDegree() < 2)
//            return SequentialClassic().multiply(p1, p2);
//
//        int half = p1.getDegree() / 2;
//
//        Polynomial p1Low = p1.getLow(half);
//        Polynomial p1High = p1.getHigh(half);
//        Polynomial p2Low = p2.getLow(half);
//        Polynomial p2High = p2.getHigh(half);
//
//        auto z1 = multiply(p1Low, p2Low);
//        auto z2 = multiply(p1Low.add(p1High), p2Low.add(p2High));
//        auto z3 = multiply(p1High, p2High);
//
//        Polynomial r1 = z3.shiftLeft(2 * half);
//        Polynomial r2 = z2.subtract(z3).subtract(z1).shiftLeft(half);
//        return r1.add(r2).add(z1);

    }
};


#endif //HOMEWORK5_SEQUENTIALKARATSUBA_H
