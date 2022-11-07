//
// Created by kamui on 07.11.2022.
//

#ifndef HOMEWORK3_RANDOM_H
#define HOMEWORK3_RANDOM_H

#include <random>

using namespace std;

// c++ generate random number https://stackoverflow.com/a/53887645/17299754
struct Random {
private:
    // random seed by default
    std::mt19937 gen_;
    std::uniform_int_distribution<size_t> dist_;

public:
    Random() : Random(0, std::numeric_limits<size_t>::max(), std::random_device{}()) {
    }

    // convenience ctor
    explicit Random(size_t max) : Random(0, max, std::random_device{}()) {
    }

    Random(size_t min, size_t max, unsigned int seed = std::random_device{}())
            : gen_{seed}, dist_{min, max} {
    }

    // if you want predictable numbers
    Random& SetSeed(unsigned int seed) {
        gen_.seed(seed);
        return *this;
    }

    size_t operator()() {
        return dist_(gen_);
    }
};


#endif //HOMEWORK3_RANDOM_H
