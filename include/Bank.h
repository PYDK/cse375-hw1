#include <map>
#include <random>
#include <mutex>
#include <chrono>
#include <iostream>
#include <atomic>
#include <thread>
#include <condition_variable>

#ifndef BANK_H
#define BANK_H

using namespace std;

class Bank {
private:
    map<int, mutex> locks;
    map<int, float> bank_accounts;
    size_t bank_size;
    atomic<int> num_dep;
    atomic<int> num_bal;
    condition_variable cv;
public:
    Bank(size_t size);
    ~Bank();
    void insert();
    void deposit(int acc1, int acc2, float amount);
    float balance();
    void do_work(int num_work, atomic<int>& counter);
};

#endif // BANK_H