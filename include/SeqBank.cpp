#include "SeqBank.h"

SeqBank::SeqBank(size_t size) {
    this->bank_size = size;
    insert();
}

SeqBank::~SeqBank() {
}

void SeqBank::insert() {
    bank_accounts.clear();
    int total = 0;
    int default_amount = 10000000/bank_size;
    for(size_t i = 0; i < bank_size; i++) {
        if(i == bank_size - 1) {
            default_amount = 10000000 - total;
        }
        bank_accounts.emplace(i, default_amount);
        total += default_amount;
    }
    printf("Total is %f\n", balance());
}

void SeqBank::deposit(int acc1, int acc2, int amount) {
    bank_accounts[acc1] += amount;
    bank_accounts[acc2] -= amount;
}

float SeqBank::balance() {
    int count = 0;
    for(size_t i = 0; i < bank_size; i++) {
        count += bank_accounts[i];
    }
    return count/100.0;
}

void SeqBank::do_work(int num_work, int& timer) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100);
    uniform_int_distribution<> dis2(0, bank_size - 1);
    uniform_int_distribution<> dis3(0, 100000);

    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num_work; i++) {
        bool check_balance = dis(gen) < 5;
        if(check_balance) {
            float bal = balance();
            if(bal < 99999.00 || bal > 100001.00) {
                printf("Balance is %.02f\n", bal);
            }
        } else {
            int account = dis2(gen);
            int account2 = dis2(gen);
            int amount = dis3(gen);
            deposit(account, account2, amount);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    if(duration.count() > timer)
        timer = duration.count();
}