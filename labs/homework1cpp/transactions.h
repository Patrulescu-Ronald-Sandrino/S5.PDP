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
//        cout << "transferring\n";
        transactions.push_back(t);
    }

    void foreach(const std::function<void(const Transaction&)>& consumer) {
        unique_lock<mutex> lock(mtx);
        printf("[T%zu] transactions.foreach() start\n", std::hash<std::thread::id>{}(std::this_thread::get_id()));
        for (const auto &transaction: transactions) {
            consumer(transaction);
        }
        printf("[T%zu] transactions.foreach() end\n", std::hash<std::thread::id>{}(std::this_thread::get_id()));
    }
};

#endif //HOMEWORK1CPP_TRANSACTIONS_H
