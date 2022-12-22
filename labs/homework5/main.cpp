#include <iostream>
#include <chrono>
#include "domain/Polynomial.h"
#include "domain/algorithms/Algorithm.h"
#include "domain/choices.h"
#include "domain/algorithms/SequentialClassic.h"
#include "domain/algorithms/ParallelClassic.h"
#include "domain/algorithms/SequentialKaratsuba.h"

using namespace std;


void run(AlgorithmType algorithmType, MethodType methodType, const Polynomial& p1, const Polynomial& p2);
void runTimed(AlgorithmType algorithmType, MethodType methodType, const Polynomial& p1, const Polynomial& p2);
void processInput(bool runOnce, AlgorithmType &algorithm, MethodType &method, const Polynomial &p1, const Polynomial &p2);


int main() {
    srand(time(nullptr));

    //////// PLAY WITH THESE VALUES ////////
    bool runOnce = false;
    AlgorithmType algorithm = AlgorithmType::REGULAR;
    MethodType method = MethodType::SEQUENTIAL;
    int degree = 5;
    // zero: p1(degree, false), random: p1(degree, true), coefficients: p1({1, 2, 3, 4, 5, 6}), mapping: p1(degree, [](unsigned int i) { return i + 1; })
    Polynomial p1(Util::vectorFromIndexMapping(degree + 1, [](unsigned int i) { return i + 1; }));
    Polynomial p2(Util::vectorFromIndexMapping(degree + 1, [](unsigned int i) { return i + 1; }));
    //////// ---------------------- ////////

    processInput(runOnce, algorithm, method, p1, p2);

    return 0;
}


Algorithm* decideAlgorithm(AlgorithmType algorithm, MethodType method) {
    // TODO: replace nullptr w/ Algorithm implementations
    if (method == MethodType::SEQUENTIAL) {
        return algorithm == AlgorithmType::REGULAR ? new SequentialClassic() : (Algorithm*) new SequentialKaratsuba();
    }
    return algorithm == AlgorithmType::REGULAR ? new ParallelClassic() : nullptr;
}

void run(AlgorithmType algorithmType, MethodType methodType, const Polynomial& p1, const Polynomial& p2) {

    if (p1.getDegree() != p2.getDegree()) {
        cout << "Degree of polynomials must be equal" << endl;
        return;
    }

    if (p1.getDegree() % 2 == 0) {
        cout << "Degree of polynomials must be odd" << endl;
        return;
    }


    [&](Algorithm *algorithm) {
        Polynomial result = algorithm->multiply(p1, p2);
        cout << "p1 * p2 = " << result;
        delete algorithm;
    }(decideAlgorithm(algorithmType, methodType));
}

void runTimed(AlgorithmType algorithmType, MethodType methodType, const Polynomial& p1, const Polynomial& p2) {
    auto start = chrono::steady_clock::now();
    run(algorithmType, methodType, p1, p2);
    auto end = chrono::steady_clock::now();

    printf(" ");
    printf(algorithmType == AlgorithmType::REGULAR ? "regular" : "karatsuba");
    printf(" ");
    printf(methodType == MethodType::SEQUENTIAL ? "sequential" : "parallel");

    std::cout << " Elapsed(ms)=" << chrono::duration_cast<chrono::microseconds>(end - start).count() << std::endl;
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
