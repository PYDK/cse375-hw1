#include "../include/SeqBank.h"
#include <unistd.h>

struct arg_t {
    int num_bank_accounts = 1000;
    int num_operations = 100000;
};

void parse_args(int argc, char* argv[], arg_t& args) {
    int opt;
    char* opts = (char*)"a:o:t:";
    while((opt = getopt(argc, argv, opts)) != -1) {
        switch(opt) {
            case 'a':
                args.num_bank_accounts = atoi(optarg);
                break;
            case 'o':
                args.num_operations = atoi(optarg);
                break;
            default:
                break;
        }
    }
}

int main(int argc, char* argv[]) {
    arg_t args;
    parse_args(argc, argv, args);
    SeqBank* bank = new SeqBank(args.num_bank_accounts);
    int timer(0);
    bank->do_work(args.num_operations, timer);
    printf("Final counter is %dms\n", timer);
    float bal = bank->balance();
    printf("Final balance is %.02f\n", bal);
    delete bank;
}