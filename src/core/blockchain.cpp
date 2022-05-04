#include "blockchain.h"

blockchain::blockchain() { }

void blockchain::genesis() {
    auto b = block(transaction::create("", "", 0), string(crypto::sha256_size, '0'));
    b.set_index(0);
    blocks.push_back(b);
    spdlog::info("Genesis block generated");
}

void blockchain::add_block(block b) {
    b.set_index(blocks.size());
    blocks.push_back(b);
    spdlog::info("block with hash ({}) is added", b.get_hash());
}

size_t blockchain::size() {
    return blocks.size();
}

vector<block> blockchain::get_blocks() {
    return blocks;
}

block blockchain::get_by_hash(string hash) {
    for(auto& b : blocks) {
        if(b.get_hash() == hash) {
            return b;
        }
    }
    throw runtime_error("no block with such hash");
}

block blockchain::get_by_prev_hash(string prev_hash) {
    for(auto& b : blocks) {
        if(b.get_prev_hash() == prev_hash) {
            return b;
        }
    }
    throw runtime_error("no block with such prev_hash");
}

block blockchain::get_last_block() {
    return blocks[blocks.size() - 1];
}

block blockchain::get_genesis_block() {
    return blocks.front();
}

bool blockchain::has_block(string hash) {
    for(auto& b : blocks) {
        if(b.get_hash() == hash) {
            return true;
        }
    }
    return false;
}
