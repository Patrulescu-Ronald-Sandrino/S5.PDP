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
    int id{};
    int balance{};
    mutex mtx{};

    static unordered_map<int, Account*> generateAccounts() {
        unordered_map<int, Account*> accounts;

        for (int i = 0; i < 10; ++i) {
            accounts[i] = generateAccount(i);
        }

        return accounts;
    }

    static Account *generateAccount(int i) {
        auto* account = new Account;
        account->id = i;
        account->balance = rand() % 1001;
        return account;
    }

    friend ostream &operator<<(ostream &os, const Account &account) {
        os << "id: " << account.id << " balance: " << account.balance;
        return os;
    }
};

#endif //HOMEWORK1CPP_ACCOUNT_H
