//region include/using {{{
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <mutex>
#include <thread>
#include <ctime>
#include <list>
#include <vector>

using std::unordered_map;
using std::string;
using std::ifstream;
using std::cout;
using std::mutex;
using std::list;
using std::vector;
//endregion }}}

//region typedef {{{
typedef struct {
    int id;
    int balance;
} Account;

typedef struct {
    int id;
    int source_id;
    int destination_id;
    int amount;
} Transaction;
//endregion }}}
// un thread care genreaza random o tranzactie
// sau n tranzactii sau intr-un for loop

//region globals {{{
#define THREADS 30
#define TRANSACTIONS_PER_THREAD 1
unordered_map<int, Account> _accounts;
int id_base;
int transaction_id_base;
mutex accounts_mutex;
mutex transaction_id_mutex;
list<Transaction> transactions;
//endregion }}}

//region accounts operations {{{
unordered_map<int, Account> read_all_accounts(const string& filename) {
   ifstream file(filename);
   Account account;
   unordered_map<int, Account> accounts;

    while(file >> account.id >> account.balance) {
        accounts[account.id] = account;
    }

    return accounts;
}

void print_all_accounts(const unordered_map<int, Account>& accounts) {
    for(auto const& account: accounts) {
        auto current = account.second;
        cout << current.id << " " << current.balance << "\n";
    }
}
//endregion }}}

//region utils {{{
int rand(int upperExclusiveBound) {
    return rand() % upperExclusiveBound;
}

int rand(int lowerBoundInclusive, int upperExclusiveBound) {
    return rand(upperExclusiveBound) + lowerBoundInclusive;
}

bool randBool() {
    return rand(2) == 1;
}
//endregion }}}

//region account workers {{{
void add_account_worker() {
    Account account;
    account.balance = rand();
    
    accounts_mutex.lock();
    
    account.id = id_base++;
    _accounts[account.id] = account;

    accounts_mutex.unlock();
}

void read_last_account_worker() {
    accounts_mutex.lock();

    auto account = _accounts[id_base - 1];
    cout << account.id << " " << account.balance << "\n";

    accounts_mutex.unlock();
}
//endregion }}}

void run_transactions_worker() {
    for(int i = 0; i < TRANSACTIONS_PER_THREAD; i++) {
        Transaction transaction;
        transaction.source_id = rand(id_base);
        // generate 2nd random id, POSSIBLY UNSAFE
        transaction.destination_id = randBool() && transaction.source_id != 0 ?
                rand(transaction.source_id) :
                rand(transaction.source_id + 1, id_base);

        // can be made into a function OR atomic integer
        transaction_id_mutex.lock();
        transaction.id = transaction_id_base++;
        transaction_id_mutex.unlock();

        auto& source_account = _accounts.at(transaction.source_id);
        const auto& source_balance = source_account.balance;
        // skip accounts with a balance of 0
        if (source_balance == 0)
            continue;
        // generate a random amount, POSSIBLY UNSAFE if balance is 0

        transaction.amount = rand(1, source_balance + 1);
        
        // subtract the amount from the source account
        // TODO: make the subtraction thread-safe
        source_account.balance -= transaction.amount;
        printf("Transaction %d from %d to %d: %d\n", transaction.id, transaction.source_id, transaction.destination_id, transaction.amount);

        // push the transaction to the list of transactions
        // TODO: make the push thread-safe
        transactions.push_front(transaction);
    }
}

void check_transactions_worker() {
    // TODO
}


int main(int argc, char** argv) {
    srand(time(nullptr));
    _accounts = read_all_accounts("accounts.txt");
    id_base = _accounts.size();

    print_all_accounts(_accounts);

    std::thread writer_thread(add_account_worker);
    std::thread reader_thread(read_last_account_worker);

    writer_thread.join();
    reader_thread.join();


    // TODO: launch, from time to time, check transaction thread & join it

    vector<std::thread> run_transactions_threads;

    for (int i = 0; i < THREADS; ++i) {
        run_transactions_threads.emplace_back(run_transactions_worker);
    }

    for (auto &runTransactionsThread: run_transactions_threads) {
        runTransactionsThread.join();
    }

    print_all_accounts(_accounts);

    return 0;
}
