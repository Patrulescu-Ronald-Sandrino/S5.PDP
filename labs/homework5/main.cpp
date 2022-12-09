#include <iostream>
#include <chrono>
#include "domain/Polynomial.h"

using namespace std;


void task(unsigned long start, unsigned long end, const Polynomial& p1, const Polynomial& p2, Polynomial& result) {
    for (unsigned long i = start; i < min(end, result.getDegree()); ++i) {

    }
}


int main() {
    srand(time(nullptr));

    Polynomial p1(5);
    Polynomial p2(5);
    cout << p1 << endl;

    auto start = chrono::steady_clock::now();
    // TODO: Implement multiplication of polynomials
    auto end = chrono::steady_clock::now();
    std::cout << "Elapsed(ms)=" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << std::endl;

    return 0;
}
