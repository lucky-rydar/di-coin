#include "gtest/gtest.h"

#include "core/blockchain.h"

TEST(blockchain, genesis)
{
    blockchain bc;
    ASSERT_EQ(bc.size(), 1);

    auto block = bc.get_blocks()[0];
    ASSERT_EQ(block.get_prev_hash(), string("Mykhailo Didur"));

    spdlog::info("{} {} {} {}", block.get_prev_hash(),
        block.get_data(), block.get_hash(), block.get_timestamp());
}

TEST(blockchain, add_block)
{
    blockchain bc;

    bc.add_block("Hello world");
    bc.add_block("send 1 BTC to user");

    ASSERT_EQ(bc.size(), 3);

    auto blocks = bc.get_blocks();

    ASSERT_EQ(blocks[0].get_data(), "Genesis Block");
    ASSERT_EQ(blocks[1].get_data(), "Hello world");
    ASSERT_EQ(blocks[2].get_data(), "send 1 BTC to user");
}
