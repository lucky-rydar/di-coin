#include "blockchain.h"

blockchain::blockchain() {
    genesis();
}

void blockchain::genesis() {
    auto b = block(genesis_str, string(crypto::sha256_size, '0'));
    blocks.push_back(b);
    spdlog::info("Genesis block generated");
}

void blockchain::add_block(string data) {
    auto b = block(data, blocks[blocks.size() - 1].get_hash());
    blocks.push_back(b);
    spdlog::info("block with hash ({}) is added", b.get_hash());
}

size_t blockchain::size() {
    return blocks.size();
}

vector<block> blockchain::get_blocks() {
    return blocks;
}