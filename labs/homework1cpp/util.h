//
// Created by kamui on 24.10.2022.
//

#ifndef HOMEWORK1CPP_UTIL_H
#define HOMEWORK1CPP_UTIL_H

#include <cstdlib>

int rand(int upperExclusiveBound) {
    return rand() % upperExclusiveBound;
}

int rand(int lowerBoundInclusive, int upperExclusiveBound) {
    return rand(upperExclusiveBound) + lowerBoundInclusive;
}

bool randBool() {
    return rand(2) == 1;
}

/**
 * @pre
 *  upperExclusiveBound > 0
 *  upperExclusiveBound > lowerBoundInclusive >= 0
 * @post
 *  first \< second
 * */
pair<int, int> generateDifferentNumbers(int lowerBoundInclusive, int upperExclusiveBound) {
    int number1 = rand(lowerBoundInclusive, upperExclusiveBound);
    int number2 = number1;

    while (number1 == number2) {
        number2 = rand(lowerBoundInclusive, upperExclusiveBound);
    }

    return make_pair(min(number1, number2), max(number1, number2));
}

#endif //HOMEWORK1CPP_UTIL_H
