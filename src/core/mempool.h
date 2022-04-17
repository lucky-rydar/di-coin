#pragma once

#include <list>
#include <string>
#include <memory>
#include <map>

#include <utils/crypto.h>
#include <core/transaction.h>

class mempool
{
    list<string> transactions_sha256_;
    map<string, transaction> transactions_;
public:
    void push(transaction transaction);

    // gets first one and removes it from mempool
    transaction pop();

    void remove_by_hash(string hash);

    int contains(string transaction_sha256);

    size_t size();
};
