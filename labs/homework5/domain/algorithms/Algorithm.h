//
// Created by kamui on 09.12.2022.
//

#ifndef HOMEWORK5_ALGORITHM_H
#define HOMEWORK5_ALGORITHM_H

#include "../Polynomial.h"

using namespace std;

class Algorithm {
public:
    virtual Polynomial multiply(const Polynomial& p1, const Polynomial& p2) = 0;
    virtual ~Algorithm() = default;
};

#endif //HOMEWORK5_ALGORITHM_H
