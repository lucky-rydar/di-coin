#include "gtest/gtest.h"

#include <core/mempool.h>

TEST(mempool, push_pop)
{
    mempool mp;
    transaction t = transaction::create("1", "2", 3);
    mp.push(t);
    ASSERT_EQ(mp.size(), 1);

    ASSERT_TRUE(mp.contains(transaction::sha256(t)));

    mp.pop();
    ASSERT_EQ(mp.size(), 0);

    ASSERT_FALSE(mp.contains(transaction::sha256(t)));
}

TEST(mempool, double_transaction)
{
    mempool mp;
    transaction doubled = transaction::create("1", "2", 3);
    transaction another = transaction::create("hello", "world", 3);
    mp.push(doubled);
    mp.push(another);
    mp.push(doubled);

    ASSERT_EQ(mp.size(), 3);

    mp.pop();
    mp.pop();
    mp.pop();
    ASSERT_EQ(mp.size(), 0);
}
