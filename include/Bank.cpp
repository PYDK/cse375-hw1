#include "Bank.h"

Bank::Bank(size_t size) {
    this->bank_size = size;
    bal_check.store(false);
    insert();
}

Bank::~Bank() {
}

void Bank::insert() {
    bank_accounts.clear();
    int total = 0;
    int default_amount = 10000000/bank_size;
    for(size_t i = 0; i < bank_size; i++) {
        if(i == bank_size - 1)
            default_amount = 10000000 - total;
        bank_accounts.insert(pair<int, float>(i, default_amount/100.00));
        total += default_amount;
    }
    printf("Total is %f\n", balance());
}

void Bank::deposit(int acc1, int acc2, float amount) {
    unique_lock<mutex> lock1(locks[acc1]);
    bank_accounts[acc1] += amount;
    lock1.unlock();
    unique_lock<mutex> lock2(locks[acc2]);
    bank_accounts[acc2] -= amount;
    lock2.unlock();
}

float Bank::balance() {
    float count = 0;
    unique_lock<shared_mutex> lock(smtx);
    for(size_t i = 0; i < bank_size; i++) {
        locks[i].lock();
    }
    lock.unlock();
    for(size_t i = 0; i < bank_size; i++) {
        count += bank_accounts[i];
        locks[i].unlock();
    }
    return round(count);
}

void Bank::do_work(int num_work, atomic<int>& timer) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100);
    uniform_int_distribution<> dis2(0, bank_size - 1);
    uniform_real_distribution<> dis3(0, 1000);

    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num_work; i++) {
        bool check_balance = dis(gen) < 5;
        if(check_balance) {
            if(bal_check.load()) {
                continue;
            }
            bal_check.store(true);
            float bal = balance();
            if(bal < 99999.00 || bal > 100001.00) {
                printf("Balance is %.02f\n", bal);
            }
            bal_check.store(false);
        } else {
            shared_lock table_lock(smtx);
            int account = dis2(gen);
            int account2 = dis2(gen);
            float amount = round((int)(dis3(gen) * 100)) / 100.0;
            deposit(account, account2, amount);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    if(duration.count() > timer.load())
        timer.store(duration.count());
}