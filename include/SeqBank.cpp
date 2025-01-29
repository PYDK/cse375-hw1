#include "SeqBank.h"

SeqBank::SeqBank(size_t size) {
    this->bank_size = size;
    insert();
}

SeqBank::~SeqBank() {
}

void SeqBank::insert() {
    bank_accounts.clear();
    float total = 0;
    float default_amount = 100000.00/bank_size;
    for(size_t i = 0; i < bank_size; i++) {
        if(i == bank_size - 1)
            default_amount = 100000.0 - total;
        bank_accounts.insert(pair<int, float>(i, default_amount));
        total += default_amount;
    }
    printf("Total is %f\n", balance());
}

void SeqBank::deposit(int acc1, int acc2, float amount) {
    bank_accounts[acc1] += amount;
    bank_accounts[acc2] -= amount;
}

float SeqBank::balance() {
    float count = 0;
    for(size_t i = 0; i < bank_size; i++) {
        count += bank_accounts[i];
    }
    return round(count);
}

void SeqBank::do_work(int num_work, int& timer) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100);
    uniform_int_distribution<> dis2(0, bank_size - 1);
    uniform_real_distribution<> dis3(0, 1000);

    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num_work; i++) {
        bool check_balance = dis(gen) < 5;
        if(check_balance) {
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
    if(duration.count() > timer)
        timer = duration.count();
}