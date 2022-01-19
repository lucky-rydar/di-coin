#pragma once

#include <utils/crypto.h>
#include "block.h"

#include <vector>

#include <spdlog/spdlog.h>

using namespace std;

class block;

class blockchain
{
private:
    const string genesis_str = "Genesis Block";

    vector<block> blocks;

    void genesis();
public:
    blockchain();

    void add_block(string data);
    size_t size();
    vector<block> get_blocks();
};
