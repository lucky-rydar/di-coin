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
};
