#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <mutex>
#include <thread>
#include <ctime>
#include <list>

using std::unordered_map;
using std::string;
using std::ifstream;
using std::cout;
using std::mutex;
using std::list;

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
// un thread care genreaza random o tranzactie
// sau n tranzactii sau intr-un for loop

unordered_map<int, Account> _accounts;
int id_base;
mutex accounts_mutex;
list<Transaction> transactions;

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

int main() {
    srand(time(0));
    _accounts = read_all_accounts("accounts.txt");
    id_base = _accounts.size();

    print_all_accounts(_accounts);

    std::thread writer_thread(add_account_worker);
    std::thread reader_thread(read_last_account_worker);

    writer_thread.join();
    reader_thread.join();


    return 0;
}
