#include <vector>

#include "gtest/gtest.h"

#include <core/miner.h>

TEST(miner, simple_mine)
{
    // should be used symbols from 0 to f
    vector<string> expected = {"", "000", "123", "fff"};
    miner m;
    block b(transaction::create("1", "2", 123), "previous hash");
    for(auto item : expected) {
        m.set_condition(item);
        m.mine(b);

        ASSERT_EQ(b.gen_hash().substr(0, item.length()), item);
    }
}
