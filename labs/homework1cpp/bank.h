//
// Created by kamui on 24.10.2022.
//

#ifndef HOMEWORK1CPP_BANK_H
#define HOMEWORK1CPP_BANK_H

#include <iostream>
#include "account.h"
#include "transactions.h"

using namespace std;

struct Bank {
    unordered_map<int, Account*> accounts;
    Transactions transactions;

    Bank() {
        accounts = Account::generateAccounts();
    }

    virtual ~Bank() {
        for (const auto &item: accounts) {
            delete item.second;
        }
    }

    void printAccounts() {
        for (const auto &item: accounts) {
            cout << *item.second << "\n";
        }
    }
};

#endif //HOMEWORK1CPP_BANK_H
