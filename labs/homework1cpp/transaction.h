//
// Created by kamui on 24.10.2022.
//

#ifndef HOMEWORK1CPP_TRANSACTION_H
#define HOMEWORK1CPP_TRANSACTION_H

struct Transaction {
    static int ID;
    const int id = ID++;

    int fromId;
    int toId;
    int amount;

    Transaction(int fromId, int toId, int amount) : fromId(fromId), toId(toId), amount(amount) {}
};

int Transaction::ID = 0;

#endif //HOMEWORK1CPP_TRANSACTION_H
