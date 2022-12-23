//
// Created by kamui on 23.12.2022.
//

#ifndef HOMEWORK5_DRIVER_H
#define HOMEWORK5_DRIVER_H

#include "domain/algorithms/SequentialKaratsuba.h"
#include "domain/algorithms/ParallelClassic.h"
#include "domain/algorithms/SequentialClassic.h"
#include "domain/choices.h"
#include "domain/algorithms/Algorithm.h"
#include "domain/Polynomial.h"
#include "domain/algorithms/ParallelKaratsuba.h"
#include <chrono>
#include <iostream>



Algorithm* decideAlgorithm(AlgorithmType algorithm, MethodType method) {
    if (method == MethodType::SEQUENTIAL) {
        return algorithm == AlgorithmType::REGULAR ? new SequentialClassic() : (Algorithm*) new SequentialKaratsuba();
    }
    return algorithm == AlgorithmType::REGULAR ? new ParallelClassic() : (Algorithm*) new ParallelKaratsuba();
}

Polynomial run(AlgorithmType algorithmType, MethodType methodType, const Polynomial& p1, const Polynomial& p2, long& duration) {
    if (p1.getDegree() != p2.getDegree()) {
        throw runtime_error("Degree of polynomials must be equal");
    }

    if (p1.getDegree() % 2 == 0) {
        throw runtime_error("Degree of polynomials must be odd");
    }

    return [&](Algorithm *algorithm) {
        auto start = chrono::high_resolution_clock::now();
        Polynomial result = algorithm->multiply(p1, p2);
        auto end = chrono::high_resolution_clock::now();

        delete algorithm;
        duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

        return result;
    }(decideAlgorithm(algorithmType, methodType));
}


string infoToString(AlgorithmType algorithmType, MethodType methodType, auto duration) {
    stringstream ss;

    string algorithm = algorithmType == AlgorithmType::REGULAR ? "Regular" : "Karatsuba";
    string method = methodType == MethodType::SEQUENTIAL ? "Sequential" : "Parallel";
    ss << "[";
    ss.width(9); ss << left << algorithm;
    ss << "  ";
    ss.width(10); ss << left << method;
    ss << "  ";
    ss.width(3); ss << right << duration;
    ss << "ms]";

    return ss.str();
}

void runTimed(AlgorithmType algorithmType, MethodType methodType, const Polynomial& p1, const Polynomial& p2) {
    long duration;
    auto result = run(algorithmType, methodType, p1, p2, duration);

    auto header = infoToString(algorithmType, methodType, duration);
    printf("%s p1 * p2 = %s\n", header.c_str(), result.toString().c_str());
}

void processInput(bool runOnce, AlgorithmType &algorithm, MethodType &method, const Polynomial &p1, const Polynomial &p2) {
    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;

    if (runOnce) {
        runTimed(algorithm, method, p1, p2);
    } else {
        runTimed(AlgorithmType::REGULAR, MethodType::SEQUENTIAL, p1, p2);
        runTimed(AlgorithmType::REGULAR, MethodType::PARALLEL, p1, p2);
        runTimed(AlgorithmType::KARATSUBA, MethodType::SEQUENTIAL, p1, p2);
        runTimed(AlgorithmType::KARATSUBA, MethodType::PARALLEL, p1, p2);
    }
}

#endif //HOMEWORK5_DRIVER_H
