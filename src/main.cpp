#include "../include/Bank.h"
#include <thread>

#define NUM_THREADS 8

int main() {
    Bank* bank = new Bank(1000);
    atomic<int> timer(0);
    vector<thread> threads;
    for(int i = 0; i < NUM_THREADS; i++) {
        threads.push_back(thread(&Bank::do_work, bank, 25000, ref(timer)));
    }
    for(auto& t : threads) {
        if(t.joinable()) {
            t.join();
        }
    }
    printf("Final counter is %dms\n", timer.load());
    float bal = bank->balance();
    printf("Final balance is %.02f\n", bal);
    delete bank;
}