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


int main() {
//    srand(time(nullptr));

    AlgorithmType algorithm = AlgorithmType::REGULAR;
    MethodType method = MethodType::SEQUENTIAL;
    int degree = 5;
//    Polynomial p1(degree);
//    Polynomial p2(degree);
    Polynomial p1({1, 2, 3, 4, 5, 6});
    Polynomial p2({1, 2, 3, 4, 5, 6});

    // SequentialClassic
    // ParallelClassic
    // SequentialKaratsuba p1 * p2 = 0*x^0 + 54*x^1 + 150*x^2 + 124*x^3 + 287*x^4 + 35*x^5 + 75*x^6 + 0*x^7
    // ParallelKaratsuba

    cout << "p1 = " << p1 << endl;
    cout << "p2 = " << p2 << endl;

    auto start = chrono::steady_clock::now();
//    run(algorithm, method, p1, p2);
    run(AlgorithmType::REGULAR, MethodType::SEQUENTIAL, p1, p2);
    run(AlgorithmType::REGULAR, MethodType::PARALLEL, p1, p2);
//    run(AlgorithmType::KARATSUBA, MethodType::SEQUENTIAL, p1, p2);
//    run(AlgorithmType::KARATSUBA, MethodType::PARALLEL, p1, p2);
    auto end = chrono::steady_clock::now();

    std::cout << "Elapsed(ms)=" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << std::endl;

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
        cout << "p1 * p2 = " << result << endl;
        delete algorithm;
    }(decideAlgorithm(algorithmType, methodType));
}