#include "../include/Bank.h"
#include <thread>
#include <unistd.h>

struct arg_t {
    int num_bank_accounts = 1000;
    int num_operations = 100000;
    int num_threads = 4;
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
            case 't':
                args.num_threads = atoi(optarg);
                break;
            default:
                break;
        }
    }
}

int main(int argc, char* argv[]) {
    arg_t args;
    parse_args(argc, argv, args);
    Bank* bank = new Bank(args.num_bank_accounts);
    atomic<int> timer(0);
    vector<thread> threads;
    int num_ops = args.num_operations/args.num_threads;
    for(int i = 0; i < args.num_threads; i++) {
        threads.push_back(thread(&Bank::do_work, bank, num_ops, ref(timer)));
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