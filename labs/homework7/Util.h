//
// Created by kamui on 09.12.2022.
//

#ifndef HOMEWORK5_UTIL_H
#define HOMEWORK5_UTIL_H

#include <vector>
#include <functional>

using namespace std;

class Util {
public:
    static vector<int> randomIntegers(int size, int min, int max) {
        vector<int> result(size);

        for (int i = 0; i < size; i++)
            result[i] = rand() % (max - min + 1) + min;

        return result;
    }

    static function<int(unsigned int)> constMapping(unsigned int k) {
        return [k](unsigned int _) { return k; };
    }

    static vector<int> vectorFromIndexMapping(int size, const function<int(unsigned int)>& mapping = constMapping(0)) {
        vector<int> result(size);
        for (int i = 0; i < size; i++)
            result[i] = mapping(i);

        return result;
    }

    static string ansiEscape(const string& content, const string& modifier) {
        return "\033[" + modifier + "m" + content + "\033[0m";
    }
};


#endif //HOMEWORK5_UTIL_H
