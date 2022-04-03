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
