#include "../include/Bank.h"

#define NUM_THREADS 4

int main() {
    Bank* bank = new Bank(1000);
    atomic<int> counter(0);
    bank->do_work(10000, counter);
    printf("Final counter is %dms\n", counter.load());
    float bal = bank->balance();
    printf("Final balance is %.02f\n", bal);
    delete bank;
}