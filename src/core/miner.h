#pragma once

#include <utils/crypto.h>

#include "block.h"

class block;

class miner
{
private:
    // this string is expected at the beginning
    string condition;
public:
    miner();
    miner(string condition);

    void mine(block& b);

    void set_condition(string condition);
    string get_condition();
    void increment_complexity();
    void decrement_complexity();
};
