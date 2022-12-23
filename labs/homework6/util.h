//
// Created by kamui on 23.12.2022.
//

#ifndef HOMEWORK6_UTIL_H
#define HOMEWORK6_UTIL_H

using namespace std;

#include <vector>
#include <string>
#include <sstream>
#include <functional>
#include <chrono>


vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

template<typename T, typename U>
vector<U> map(const vector<T>& elements, U (*mapper)(const T&)) {
    vector<U> result;
    for (const string& e : elements) {
        result.push_back(mapper(e));
    }
    return result;
}

bool contains(const vector<int>& elements, int element) {
    for (int e : elements) {
        if (e == element) return true;
    }
    return false;
}

template<typename T>
vector<T> vectorFromIndexMapping(int size, const function<T(unsigned int)>& mapping) {
    vector<T> result(size);
    for (int i = 0; i < size; i++)
        result[i] = mapping(i);

    return result;
}


#endif //HOMEWORK6_UTIL_H
