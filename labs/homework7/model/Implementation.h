//
// Created by kamui on 13.01.2023.
//

#ifndef HOMEWORK7_IMPLEMENTATION_H
#define HOMEWORK7_IMPLEMENTATION_H

#endif //HOMEWORK7_IMPLEMENTATION_H

enum Implementation {
    regular,
    karatsuba
};

string implementationToString(Implementation implementation) {
    switch (implementation) {
        case Implementation::regular:
            return "Regular";
        case karatsuba:
            return "Karatsuba";
    }
}