#include <iostream>
#include <chrono>
#include "../homework7/model/Polynomial.h"
#include "domain/choices.h"
#include "driver.h"

using namespace std;


int main() {
    srand(time(nullptr));

    //////// PLAY WITH THESE VALUES ////////
    bool runOnce = false;
    bool printPolynomials = false;
    AlgorithmType algorithm = AlgorithmType::REGULAR;
    MethodType method = MethodType::SEQUENTIAL;
    int degree = 20001;
    // zero: p1(degree, false), random: p1(degree, true), coefficients: p1({1, 2, 3, 4, 5, 6}), mapping: p1(degree, [](unsigned int i) { return i + 1; })
    Polynomial p1(Util::vectorFromIndexMapping(degree + 1, [](unsigned int i) { return (i + 1) % 10; }));
    Polynomial p2(Util::vectorFromIndexMapping(degree + 1, [](unsigned int i) { return (i + 1) % 10; }));
    //////// ---------------------- ////////

    processInput(runOnce, algorithm, method, p1, p2, printPolynomials);

    return 0;
}



