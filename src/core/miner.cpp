#include "miner.h"

miner::miner(string condition)
        : condition(condition) {
    if(condition.length() > crypto::sha256_size) {
        throw logic_error("difficulty cant be bigger than hash size(64 bytes)");
    }
}

miner::miner()
        : condition("") {
}

void miner::mine(block& b) {
    uint64_t max_uint64 = std::numeric_limits<uint64_t>::max();
    auto begin = chrono::steady_clock::now();
    spdlog::info("mining...");

    for(uint64_t nonce = 0; nonce != max_uint64; nonce++) {
        b.set_nonce(nonce);
        auto proof_str = b.gen_hash().substr(0, condition.length());
        if(proof_str == condition) {
            auto end = chrono::steady_clock::now();
            spdlog::info("found!\nhash: {}\nnonce: {}\ntook: {}ms", b.gen_hash(), nonce,
                chrono::duration_cast<chrono::milliseconds>(end - begin).count());

            return;
        }
    }
    throw runtime_error("unminable");
}

void miner::set_condition(string condition) {
    if(condition.length() > crypto::sha256_size) {
        throw logic_error("difficulty cant be bigger than hash size(64 bytes)");
    }
    this->condition = condition;
}

string miner::get_condition() {
    return condition;
}

void miner::increment_complexity() {
    if(condition.length() >= 0 && condition.length() < crypto::sha256_size)
        set_condition(string(condition.length() + 1, '0'));
}

void miner::decrement_complexity() {
    if(condition.length() > 0 && condition.length() <= crypto::sha256_size)
        set_condition(string(condition.length() - 1, '0'));
}
