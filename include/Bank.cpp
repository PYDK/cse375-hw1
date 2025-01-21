#include "Bank.h"

Bank::Bank(size_t size) {
    bank_size = size;
    insert();
}

Bank::~Bank() {
    bank_accounts.remove();
}

void Bank::insert() {
    bank_accounts.clear();
    for(int i = 0; i < bank_size; i++) {
        Account acct;
        acct.id = i;
        acct.acct_balance = 0.0;
        bank_accounts.insert(acct);
    }
    int total = 10000000;
    while(total > 0) {
        int acct_id = rand() % bank_size;
        float deposit = (rand() % total) / 100.0;
        total -= deposit;
        bank_accounts[acct_id].acct_balance += deposit;
    }
}