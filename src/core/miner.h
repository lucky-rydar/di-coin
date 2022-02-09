#pragma once

#include <utils/crypto.h>

#include "block.h"

class block;

class miner
{
private:
    // this string is expected at the beginning
    string expected_string;
    uint64_t difficulty;
public:
    miner(string expected_string);

    void mine(block& b);
};
