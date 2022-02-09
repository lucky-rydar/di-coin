#include "miner.h"

miner::miner(string expected_string)
        : expected_string(expected_string) {
    difficulty = expected_string.length();
    if(difficulty > crypto::sha256_size) {
        throw logic_error("difficulty cant be bigger than hash size(64 bytes)");
    }
}

void miner::mine(block& b) {
    uint64_t max_uint64 = std::numeric_limits<uint64_t>::max();
    auto begin = chrono::steady_clock::now();
    spdlog::info("mining...");

    for(uint64_t nonce = 0; nonce != max_uint64; nonce++) {
        b.set_nonce(nonce);
        auto proof_str = b.gen_hash().substr(0, difficulty);
        if(proof_str == expected_string) {
            auto end = chrono::steady_clock::now();
            spdlog::info("found!\nhash: {}\nnonce: {}\ntook: {}ms", b.gen_hash(), nonce,
                chrono::duration_cast<chrono::milliseconds>(end - begin).count());

            return;
        }
    }
    throw runtime_error("unminable");
}
