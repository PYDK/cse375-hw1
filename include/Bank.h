#include <map>
#include <cstdio>
#include <random>
#include <mutex>
#include <chrono>
#include <iostream>
#include <atomic>

#ifndef BANK_H
#define BANK_H

using namespace std;

class Bank {
private:
    struct BankAccount {
        mutex mtx;
        float balance;
    };
    map<int, BankAccount*> bank_accounts;
    size_t bank_size;
    size_t num_threads;
public:
    Bank(size_t size);
    ~Bank();
    void insert();
    void deposit(int acc1, int acc2, float amount);
    float balance();
    void do_work(int num_work, atomic<int>& counter);
};

#endif // BANK_H