#include <iostream>
#include <thread>
#include "bank.h"

using namespace std;

#define RUN_TRANSACTION_WORKERS 10
#define CHECK_TRANSACTIONS_WORKERS 5

Bank bank;

void runTransactionWorker() {
    std::this_thread::sleep_for(std::chrono::milliseconds(0));

    pair<int, int> accountIds = Bank::getRandomAccountIds();
    if (accountIds.first >= accountIds.second) {
        perror("first >= second");
        exit(1);
    }
    int amount = rand(Account::MAX_INITIAL_BALANCE + 1);

    if (bank.transfer(accountIds.first, accountIds.second, amount)) {
        printf("Transferred from %d to %d: %d\n", accountIds.first, accountIds.second, amount);
    }
}

void checkTransactionsWorker() {
    // get the initial balance of each account
    unordered_map<int, int> accountsBalances = bank.getAccountsInitialBalances();

    // compute the balance of each account after all the transactions
    unique_lock writeLock(bank.accountsMutex);
    printf("check() ...\n");
    bank.transactions.foreach([&](const Transaction &t) {
        accountsBalances[t.fromId] -= t.amount;
        accountsBalances[t.toId] += t.amount;
    });

    // compare the actual balance with the expected balance for each account
    for (auto &item: bank.accounts) {
        Account& account = *item.second;
        unique_lock<mutex> lock(account.mtx);
        const auto expected = accountsBalances[account.id];
        if (account.balance != expected) {
            printf("balance mismatch for account %d. expected: %d, actual: %d\n", account.id, expected, account.balance);
        }
        else {
//            printf("ok account %d\n", account.id);
        }
    }
}


int main() {
    srand(time(0));
//    srand(200);

    bank.printAccounts();

    vector<thread> runTransactionThreads;
    vector<thread> checkTransactionsThreads;

    for (int i = 0; i < RUN_TRANSACTION_WORKERS; ++i) {
        checkTransactionsThreads.emplace_back(&checkTransactionsWorker);
        runTransactionThreads.emplace_back(&runTransactionWorker);
//        checkTransactionsThreads.emplace_back(&checkTransactionsWorker);
    }

    for (int i = 0; i < CHECK_TRANSACTIONS_WORKERS; ++i) {
//        checkTransactionsThreads.emplace_back(&checkTransactionsWorker);
//        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }


    // launch final check of transactions
    for (int i = 0; i < runTransactionThreads.size(); ++i) {
        runTransactionThreads[i].join();
    }
//    for (auto &runTransactionThread: runTransactionThreads) {
//        runTransactionThread.join();
//    }

    for (auto &checkTransactionsThread: checkTransactionsThreads) {
        checkTransactionsThread.join();
    }
    thread checkTransactionsThread(&checkTransactionsWorker);
    checkTransactionsThread.join();

    bank.printAccounts();

    return 0;
}
