#include <map>
#include <random>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <atomic>
#include <vector>

#ifndef BANK_H
#define BANK_H

using namespace std;

class Bank {
private:
    atomic<bool> bal_check; // atomic bool to prevent multiple concurrent balance checks
    shared_mutex smtx; // shared mutex to lock the lock table
    map<int, mutex> locks; // map of mutexes to lock each account
    map<int, float> bank_accounts; // map of account number to balance
    size_t bank_size;
public:
    Bank(size_t size);
    ~Bank();
    void insert();
    void deposit(int acc1, int acc2, float amount);
    float balance();
    void do_work(int num_work, atomic<int>& counter);
};

#endif // BANK_H