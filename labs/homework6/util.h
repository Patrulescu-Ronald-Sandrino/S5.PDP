//
// Created by kamui on 23.12.2022.
//

#ifndef HOMEWORK6_UTIL_H
#define HOMEWORK6_UTIL_H

using namespace std;

#include <vector>
#include <string>
#include <sstream>


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


#endif //HOMEWORK6_UTIL_H
