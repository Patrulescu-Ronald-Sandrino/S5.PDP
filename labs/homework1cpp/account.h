//
// Created by kamui on 24.10.2022.
//

#ifndef HOMEWORK1CPP_ACCOUNT_H
#define HOMEWORK1CPP_ACCOUNT_H

#include <mutex>
#include <unordered_map>
#include <memory>
#include <ostream>

using namespace std;

struct Account {
    static const int MAX_INITIAL_BALANCE = 1000;

    int id{};
    int initialBalance{};
    int balance{};
    mutex mtx{};

    static unordered_map<int, Account*> generateAccounts(int number) {
        unordered_map<int, Account*> accounts;

        for (int i = 0; i < number; ++i) {
            accounts[i] = generateAccount(i);
        }

        return accounts;
    }

    static Account *generateAccount(int i) {
        auto* account = new Account;
        account->id = i;
        account->balance = account->initialBalance = rand() % (MAX_INITIAL_BALANCE + 1);
        return account;
    }

    friend ostream &operator<<(ostream &os, const Account &account) {
        os << "id: " << account.id << " balance: " << account.balance;
        return os;
    }
};

#endif //HOMEWORK1CPP_ACCOUNT_H
