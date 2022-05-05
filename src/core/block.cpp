#include "block.h"

block::block(transaction transaction_, string prev_hash) {
    this->prev_hash = prev_hash;
    this->transaction_ = transaction_;
    gen_timestamp();
    gen_hash();
}

void block::operator=(const block& b) {
    prev_hash = b.prev_hash;
    transaction_ = b.transaction_;
    timestamp = b.timestamp;
    hash = b.hash;
    nonce = b.nonce;
    index = b.index;
}

string block::gen_hash() {
    hash = crypto::sha256(prev_hash + to_string(::jsonify(transaction_)) + timestamp + to_string(nonce));
    return hash;
}

void block::gen_timestamp() {
    this->timestamp = tu::timestamp();
}

void block::actualize() {
    gen_timestamp();
    gen_hash();
}

string block::get_hash() {
    return hash;
}

string block::get_prev_hash() {
    return prev_hash;
}

string block::get_timestamp() {
    return timestamp;
}

string block::get_data() {
    return to_string(::jsonify(transaction_));
}

transaction block::get_transaction() {
    return transaction_;
}

void block::set_nonce(uint64_t nonce) {
    this->nonce = nonce;
}

int block::get_index() {
    return index;
}

void block::set_index(int index) {
    this->index = index;
}

json block::jsonify() {
    json ret = {
        {"timestamp", timestamp},
        {"transaction", ::jsonify(transaction_)},
        {"prev_hash", prev_hash},
        {"hash", hash},
        {"nonce", nonce},
        {"index", index}
    };
    return ret;
}
