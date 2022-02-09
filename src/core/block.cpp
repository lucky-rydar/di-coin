#include "block.h"

block::block(string data, string prev_hash) {
    this->prev_hash = prev_hash;
    this->data = data;
    gen_timestamp();
    gen_hash();
}

void block::operator=(const block& b) {
    prev_hash = b.prev_hash;
    data = b.data;
    timestamp = b.timestamp;
    hash = b.hash;
    nonce = b.nonce;
}

string block::gen_hash() {
    hash = crypto::sha256(prev_hash + data + timestamp + to_string(nonce));
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
    return data;
}

void block::set_nonce(uint64_t nonce) {
    this->nonce = nonce;
}
