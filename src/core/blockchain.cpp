#include "blockchain.h"

blockchain::blockchain()
        : miner_(miner_condition) {
}

void blockchain::genesis() {
    auto b = block(transaction::create("", "", 0), string(crypto::sha256_size, '0'));
    blocks.push_back(b);
    spdlog::info("Genesis block generated");
}

void blockchain::add_transaction(transaction t) {
    auto b = block(t, blocks[blocks.size() - 1].get_hash());
    miner_.mine(b);
    blocks.push_back(b);
    spdlog::info("block with hash ({}) is added", b.get_hash());
}

size_t blockchain::size() {
    return blocks.size();
}

vector<block> blockchain::get_blocks() {
    return blocks;
}
