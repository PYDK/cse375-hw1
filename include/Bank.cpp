#include "Bank.h"

Bank::Bank(size_t size) {
    this->bank_size = size;
    num_dep.store(0);
    num_bal.store(0);
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
        bank_accounts.insert(pair<int, float>(i, default_amount));
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
    for(size_t i = 0; i < bank_size; i++) {
        count += bank_accounts[i];
    }
    return round(count);
}

void Bank::do_work(int num_work, atomic<int>& timer) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100);
    uniform_int_distribution<> dis2(0, bank_size - 1);
    uniform_real_distribution<> dis3(0, 1000);
    mutex m;
    unique_lock<mutex> lock_guard(m);

    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num_work; i++) {
        num_dep.fetch_add(1);
        bool check_balance = dis(gen) < 5;
        if(check_balance) {
            num_dep.fetch_sub(1);
            while(num_dep.load() != 0) {
                std::this_thread::yield();
            }
            num_bal.fetch_add(1);
            float bal = balance();
            if(bal != 100000.0) {
                printf("Balance is %.02f\n", bal);
            }
            num_bal.fetch_sub(1);
            if(num_bal.load() == 0) {
                cv.notify_all();
            }
        } else {
            int account = dis2(gen);
            int account2 = dis2(gen);
            float amount = dis3(gen);
            deposit(account, account2, amount);
            num_dep.fetch_sub(1); // There is no guarantee that the worker will wait before the balance check finishes
        }

        if(num_bal.load()) {
            cv.wait(lock_guard, [&] { return num_bal.load() == 0; });
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    if(duration.count() > timer.load())
        timer.store(duration.count());
}