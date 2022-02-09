#pragma once
#include <chrono>

#include <utils/crypto.h>
#include <utils/time_utils.h>

#include "blockchain.h"
#include "miner.h"

namespace tu = time_utils;

class block
{
    string timestamp;
    string data;
    string prev_hash;
    string hash;
    uint64_t nonce;

    void gen_timestamp();

    void actualize();

public:
    block(string data, string prev_hash);

    void operator=(const block& b);

    string gen_hash();
    string get_hash();
    string get_prev_hash();
    string get_timestamp();
    string get_data();
    void set_nonce(uint64_t nonce);
};
