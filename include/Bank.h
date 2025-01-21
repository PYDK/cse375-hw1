#include <map>
#include <stdio>

#ifdef BANK_H
#define BANK_H

using namespace std;

struct Account {
    int id;
    float acct_balance;
}

class Bank {
private:
    map<Account> bank_accounts;
    size_t bank_size;
public:
    Bank();
    ~Bank();
    void insert();
    void deposit();
    void balance();
    void do_work();
    void remove();
};

#endif // BANK_H