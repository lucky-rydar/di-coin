#include "gtest/gtest.h"
#include <fort.hpp>

#include <core/blockchain.h>

using namespace std;

void print_block(block block) {
    fort::char_table table;

    table << fort::header;
    table.write_ln("", "Block");

    table.write_ln("data", block.get_data());
    table.write_ln("timestamp", block.get_timestamp());
    table.write_ln("nonce", to_string(block.get_nonce()));
    table.write_ln("hash", block.get_hash());
    table.write_ln("prev hash", block.get_prev_hash());

    spdlog::info("\n{}", table.to_string());
}

TEST(lab1, demo1)
{
    blockchain b;

    this_thread::sleep_for(chrono::milliseconds(5));

    b.add_block("zero transaction");

    for(auto b : b.get_blocks()) {
        print_block(b);
    }
}
