#include "../include/SeqBank.h"

#define NUM_THREADS 4

int main() {
    SeqBank* bank = new SeqBank(1000);
    int timer(0);
    bank->do_work(100000, timer);
    printf("Final counter is %dms\n", timer);
    float bal = bank->balance();
    printf("Final balance is %.02f\n", bal);
    delete bank;
}