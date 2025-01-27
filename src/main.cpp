#include "../include/Bank.h"
#include <chrono>
#include <iostream>

void do_work(Bank* bank, int work) {
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < work; i++) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 100);
        if(dis(gen) < 5) {
            float bal = bank->balance();
            if(bal != 100000.0) {
                printf("Balance is %.02f\n", bal);
                exit(1);
            }
        } else {
            bank->deposit();
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;
}

int main() {
    Bank* bank = new Bank(1000);
    do_work(bank, 10000);
    delete bank;
}