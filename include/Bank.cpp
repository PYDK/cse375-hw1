#include "Bank.h"

Bank::Bank(size_t size) {
    this->bank_size = size;
    insert();
}

Bank::~Bank() {
    for(size_t i = 0; i < bank_size; i++) {
        delete bank_accounts[i];
    }
    bank_accounts.clear();
}

void Bank::insert() {
    bank_accounts.clear();
    float total = 0;
    float default_amount = 100000.00/bank_size;
    for(size_t i = 0; i < bank_size; i++) {
        if(i == bank_size - 1)
            default_amount = 100000.0 - total;
        BankAccount* acc = new BankAccount();
        acc->balance = default_amount;
        bank_accounts.insert(pair<int, BankAccount*>(i, acc));
        total += default_amount;
    }
    printf("Total is %f\n", balance());
}

void Bank::deposit(int acc1, int acc2, float amount) {
    // unique_lock<mutex> lock1(bank_accounts[account]->mtx, defer_lock);
    bank_accounts[acc1]->balance += amount;
    bank_accounts[acc2]->balance -= amount;
}

float Bank::balance() {
    float count = 0;
    for(size_t i = 0; i < bank_size; i++) {
        count += bank_accounts[i]->balance;
    }
    return round(count);
}

void Bank::do_work(int num_work, atomic<int>& counter) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100);
    uniform_int_distribution<> dis2(0, bank_size - 1);
    uniform_real_distribution<> dis3(0, 1000);
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num_work; i++) {
        if(dis(gen) < 5) {
            float bal = balance();
            if(bal != 100000.0) {
                printf("Balance is %.02f\n", bal);
                exit(1);
            }
        } else {
            int account = dis2(gen);
            int account2 = dis2(gen);
            float amount = dis3(gen);
            deposit(account, account2, amount);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    counter.fetch_add(duration.count());
}