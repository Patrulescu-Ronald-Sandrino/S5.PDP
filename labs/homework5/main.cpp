#include <iostream>
#include <chrono>
#include "domain/Polynomial.h"
#include "domain/choices.h"
#include "driver.h"

using namespace std;


int main() {
    srand(time(nullptr));

    //////// PLAY WITH THESE VALUES ////////
    bool runOnce = false;
    AlgorithmType algorithm = AlgorithmType::REGULAR;
    MethodType method = MethodType::SEQUENTIAL;
    int degree = 501;
    // zero: p1(degree, false), random: p1(degree, true), coefficients: p1({1, 2, 3, 4, 5, 6}), mapping: p1(degree, [](unsigned int i) { return i + 1; })
    Polynomial p1(Util::vectorFromIndexMapping(degree + 1, [](unsigned int i) { return i + 1; }));
    Polynomial p2(Util::vectorFromIndexMapping(degree + 1, [](unsigned int i) { return i + 1; }));
    //////// ---------------------- ////////

    processInput(runOnce, algorithm, method, p1, p2);

    return 0;
}



