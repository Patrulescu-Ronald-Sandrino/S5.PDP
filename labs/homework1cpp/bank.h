//
// Created by kamui on 24.10.2022.
//

#ifndef HOMEWORK1CPP_BANK_H
#define HOMEWORK1CPP_BANK_H

#include <iostream>
#include <shared_mutex>
#include "account.h"
#include "transactions.h"
#include "util.h"

using namespace std;

struct Bank {
    static const int ACCOUNTS; // id in range [0, ACCOUNTS)

    unordered_map<int, Account*> accounts;
    Transactions transactions;
    shared_mutex accountsMutex;

    Bank() {
        accounts = Account::generateAccounts(ACCOUNTS);
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

    unordered_map<int, int> getAccountsInitialBalances() {
        unordered_map<int, int> accountsInitialBalances;

        for (const auto &item: accounts) {
            accountsInitialBalances[item.first] = item.second->initialBalance;
        }

        return accountsInitialBalances;
    }

    /**
     * post-condition: first < second
     */
    static pair<int, int> getRandomAccountIds() {
        return generateDifferentNumbers(0, ACCOUNTS);
    }

    bool transfer(int fromId, int toId, int amount);
};

const int Bank::ACCOUNTS = 10;

/**
 * @pre
 * fromId \< toId*/
bool Bank::transfer(int fromId, int toId, int amount) {
    shared_lock readLock(accountsMutex);

    auto& fromAccount = *accounts[fromId];
    auto& toAccount = *accounts[toId];

//    transactions.mtx.lock();
    unique_lock<mutex> lock(transactions.mtx);
    fromAccount.mtx.lock();
    toAccount.mtx.lock();

    if (fromAccount.balance < amount) {
        fromAccount.mtx.unlock();
        toAccount.mtx.unlock();
        return false;
    }

    fromAccount.balance -= amount;

//    unique_lock<mutex> toLock(toAccount.mtx);

//    transactions.add(Transaction(fromId, toId, amount));
    transactions.transactions.emplace_back(fromId, toId, amount);

    printf("transferring from %d to %d: %d\n", fromId, toId, amount);


    toAccount.balance += amount;
    toAccount.mtx.unlock();
    fromAccount.mtx.unlock();

//    transactions.mtx.unlock();

    return true;
}

#endif //HOMEWORK1CPP_BANK_H
