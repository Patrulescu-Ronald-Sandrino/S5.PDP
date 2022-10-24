//
// Created by kamui on 24.10.2022.
//

#ifndef HOMEWORK1CPP_TRANSACTIONS_H
#define HOMEWORK1CPP_TRANSACTIONS_H

#include <list>
#include <mutex>
#include <functional>
#include "transaction.h"

using namespace std;

struct Transactions {
    list<Transaction> transactions;
    mutex mtx;

    void add(Transaction t) {
        unique_lock<mutex> lock(mtx);

        transactions.push_back(t);
    }

    void foreach(const std::function<void(const Transaction&)>& consumer) {
        unique_lock<mutex> lock(mtx);

        for (const auto &transaction: transactions) {
            consumer(transaction);
        }
    }
};

#endif //HOMEWORK1CPP_TRANSACTIONS_H
