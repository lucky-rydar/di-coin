#pragma once

#include <utils/crypto.h>

#include <core/block.h>

#include <vector>

#include <spdlog/spdlog.h>

using namespace std;

class block;

class blockchain
{
private:
    const string genesis_str = "Genesis Block";

    vector<block> blocks;

public:
    blockchain();

    void genesis();
    void add_block(block b);
    size_t size();
    vector<block> get_blocks();
    void clear();

    block get_by_hash(string hash);
    block get_by_prev_hash(string prev_hash);
    block get_last_block();
    block get_genesis_block();

    bool has_block(string hash);
};
