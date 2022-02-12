#include "gtest/gtest.h"

#include <fort.hpp>
#include <core/block.h>

using namespace fort;

TEST(libfort, libfort1)
{
    block b("Genesis block", string(64, '0'));
    miner m("0000");
    m.mine(b);

    char_table table;
    table << fort::header
        << "" << "Block" << fort::endr
        << "timestamp" << b.get_timestamp() << fort::endr
        << "data" << b.get_data() << fort::endr
        << "hash" << b.get_hash() << fort::endr
        << "previous hash" << b.get_prev_hash() << fort::endr;

    cout << table.to_string() << endl;
}
