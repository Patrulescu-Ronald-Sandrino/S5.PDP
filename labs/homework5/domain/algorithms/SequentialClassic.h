//
// Created by kamui on 16.12.2022.
//

#ifndef HOMEWORK5_SEQUENTIALCLASSIC_H
#define HOMEWORK5_SEQUENTIALCLASSIC_H


#include "Algorithm.h"

class SequentialClassic : public Algorithm {

public:
    Polynomial multiply(const Polynomial& p1, const Polynomial& p2) override {
        Polynomial result(p1.getDegree() + p2.getDegree(), false);

        for (int i = 0; i <= p1.getDegree(); i++) {
            for (int j = 0; j <= p2.getDegree(); j++) {
                result[i + j] += p1[i] * p2[j];
            }
        }

        return result;
    };
};


#endif //HOMEWORK5_SEQUENTIALCLASSIC_H
