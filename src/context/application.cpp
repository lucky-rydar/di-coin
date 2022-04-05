#include "application.h"

application::application() {
    blockchain_.genesis();
}

void application::add_transaction(string from, string to, int amount) {
    if(amount <= 0) {
        throw invalid_transaction_exception();
    }

    if(accounts_.find(from) == accounts_.end()) {
        accounts_[from] = 0;
    }

    if(accounts_.find(to) == accounts_.end()) {
        accounts_[to] = 0;
    }

    if(accounts_[from] < amount) {
        throw invalid_transaction_exception();
    }

    blockchain_.add_transaction(transaction::create(from, to, amount));
    accounts_[from] -= amount;
    accounts_[to] += amount;
}

void application::emit_coins(string to, int amount) {
    if(amount <= 0) {
        throw invalid_transaction_exception();
    }

    if(accounts_.find(to) == accounts_.end()) {
        accounts_[to] = 0;
    }

    blockchain_.add_transaction(transaction::coinbase(to, amount));
    accounts_[to] += amount;
}

int application::get_balance(string account) {
    if(accounts_.find(account) == accounts_.end()) {
        return 0;
    }

    return accounts_[account];
}

vector<block> application::get_blocks() {
    return blockchain_.get_blocks();
}
