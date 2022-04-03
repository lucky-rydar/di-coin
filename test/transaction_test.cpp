#include "gtest/gtest.h"
#include <core/transaction.h>

TEST(transaction, create)
{
    auto t = transaction::create("from", "to", 100);
    ASSERT_EQ(t.from, "from");
    ASSERT_EQ(t.to, "to");
    ASSERT_EQ(t.amount, 100);
}

TEST(transaction, coinbase)
{
    auto t = transaction::coinbase("to", 100);
    ASSERT_EQ(t.from, "");
    ASSERT_EQ(t.to, "to");
    ASSERT_EQ(t.amount, 100);
}
