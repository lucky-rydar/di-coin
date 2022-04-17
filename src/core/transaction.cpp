#include "transaction.h"

json transaction::jsonify() {
    json ret = {
        {"from", from},
        {"to", to},
        {"amount", amount}
    };
    return ret;
}

transaction transaction::coinbase(string to, uint64_t amount) {
    transaction ret;
    ret.from = "";
    ret.to = to;
    ret.amount = amount;
    return ret;
}

transaction transaction::create(string from, string to, uint64_t amount) {
    transaction ret;
    ret.from = from;
    ret.to = to;
    ret.amount = amount;
    return ret;
}

string transaction::sha256(transaction t) {
    return crypto::sha256(t.from + "_" + t.to + "_" + to_string(t.amount));
}
