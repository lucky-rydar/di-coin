#include "gtest/gtest.h"

#include <core/miner.h>

TEST(miner, simple_mine)
{
    string expected = "0000";
    miner m("0000");
    block b("hello", "previous hash");
    m.mine(b);

    ASSERT_EQ(b.gen_hash().substr(0, expected.length()), expected);
}
