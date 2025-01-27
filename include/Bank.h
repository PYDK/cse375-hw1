#include <map>
#include <cstdio>
#include <random>

#ifndef BANK_H
#define BANK_H

using namespace std;

class Bank {
private:
    map<int, float> bank_accounts;
    size_t bank_size;
public:
    Bank(size_t size);
    ~Bank();
    void insert();
    void deposit();
    float balance();
};

#endif // BANK_H