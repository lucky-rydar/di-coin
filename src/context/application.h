#pragma once

#include <memory>
#include <string>
#include <map>
#include <iostream>

#include "core/blockchain.h"

using namespace std;

class invalid_transaction_exception : public exception {
public:
    const char* what() const noexcept override {
        return "Invalid transaction";
    }
};

typedef map<string, int> accounts;

class application
{
    accounts accounts_;
    blockchain blockchain_;

    application();
public:
    static application& instance() {
        static application instance;
        return instance;
    }

    void add_transaction(string from, string to, int amount);
    void emit_coins(string to, int amount);
    int get_balance(string account);
    vector<block> get_blocks();
};
