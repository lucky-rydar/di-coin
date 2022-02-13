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
    string miner_condition = "0000";
    miner miner_;

    void genesis();
public:
    blockchain();

    void add_block(transaction t);
    size_t size();
    vector<block> get_blocks();
};
