//
// Created by kamui on 09.12.2022.
//

#ifndef HOMEWORK5_UTIL_H
#define HOMEWORK5_UTIL_H

#include <vector>

using namespace std;

class Util {
public:
    static vector<int> randomIntegers(int size, int min, int max) {
        vector<int> result;
        for (int i = 0; i < size; i++) {
            result.push_back(rand() % (max - min + 1) + min);
        }
        return result;
    }
};


#endif //HOMEWORK5_UTIL_H
