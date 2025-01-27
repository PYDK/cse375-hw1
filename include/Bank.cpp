#include "Bank.h"

Bank::Bank(size_t size) {
    bank_size = size;
    insert();
}

Bank::~Bank() {
}

void Bank::insert() {
    bank_accounts.clear();
    float total = 0;
    float default_amount = 100000.00/bank_size;
    for(size_t i = 0; i < bank_size; i++) {
        if(i == bank_size - 1)
            default_amount = 100000.0 - total;
        bank_accounts.insert(pair<int, float>(i , default_amount));
        total += default_amount;
    }
    printf("Total is %f\n", balance());
}

void Bank::deposit() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, bank_size - 1);
    int account = dis(gen);
    int account2 = dis(gen);
    uniform_real_distribution<> dis2(0, 1000);
    float amount = (float) dis2(gen);
    bank_accounts[account] += amount;
    bank_accounts[account2] -= amount;
}

float Bank::balance() {
    float count = 0;
    for(size_t i = 0; i < bank_size; i++) {
        count += bank_accounts[i];
    }
    return round(count);
}