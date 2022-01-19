#pragma once
#include <utils/crypto.h>
#include <utils/time_utils.h>

#include "blockchain.h"

namespace tu = time_utils;

class block
{
    string timestamp;
    string data;
    string prev_hash;
    string hash;

    void gen_hash();
    void gen_timestamp();

    void actualize();

public:
    block(string data, string prev_hash);

    void operator=(const block& b);

    string get_hash();
    string get_prev_hash();
    string get_timestamp();
    string get_data();
};
