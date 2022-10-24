#include <iostream>
#include "bank.h"

int main() {
    srand(time(nullptr));

    Bank bank;
    bank.printAccounts();

    return 0;
}
