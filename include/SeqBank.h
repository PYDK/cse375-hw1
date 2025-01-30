#include <map>
#include <random>
#include <chrono>
#include <iostream>

#ifndef BANK_H
#define BANK_H

using namespace std;

class SeqBank {
private:
    map<int, int> bank_accounts; // map of account number to balance
    size_t bank_size;
public:
    SeqBank(size_t size);
    ~SeqBank();
    void insert();
    void deposit(int acc1, int acc2, int amount);
    float balance();
    void do_work(int num_work, int& counter);
};

#endif // BANK_H