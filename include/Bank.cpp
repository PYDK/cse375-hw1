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
    float count = 0;
    for(size_t i = 0; i < bank_size; i++) {
        count += bank_accounts[i];
    }
    printf("Total: $%.5f\n", count);
}