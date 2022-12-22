//
// Created by kamui on 16.12.2022.
//

#ifndef HOMEWORK5_PARALLELCLASSIC_H
#define HOMEWORK5_PARALLELCLASSIC_H

#include <thread>
#include "Algorithm.h"

using namespace std;

class ParallelClassic : public Algorithm {
public:
    static const int NUMBER_OF_THREADS = 4;

    Polynomial multiply(const Polynomial &p1, const Polynomial &p2) override {
        Polynomial result(p1.getDegree() + p2.getDegree(), false);
        int size = result.getNumberOfCoefficients();
        int step = max(size / NUMBER_OF_THREADS, 1); // avoid step = 0 by maxing w/ 1
        vector<thread> threads;

        for (int sublistStart = 0; sublistStart < size; sublistStart += step) {
            int sublistEndExclusive = sublistStart + step;

            threads.emplace_back([=, &result, &p1, &p2] {
                for (int i = sublistStart; i < sublistEndExclusive && i <= size; i++) {
                    for (int j = 0; j <= i; ++j) {
                        if (j < p1.getNumberOfCoefficients() and i - j < p2.getNumberOfCoefficients()) {
                            result[i] += p1[j] * p2[i - j];
                        }
                    }
                }
            });
        }

        for (auto &thread: threads) thread.join();

        return result;
    }
};


#endif //HOMEWORK5_PARALLELCLASSIC_H
