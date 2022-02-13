#include "gtest/gtest.h"

#include "core/blockchain.h"
#include "core/transaction.h"
#include <vector>

using namespace std;

TEST(blockchain, genesis)
{
    blockchain bc;
    ASSERT_EQ(bc.size(), 1);

    auto block = bc.get_blocks()[0];
    ASSERT_EQ(block.get_prev_hash(), string(64, '0'));

    spdlog::info("{}", to_string(jsonify(block)));
}

TEST(blockchain, add_block)
{
    blockchain bc;

    vector<transaction> transactions = {
        {"1", "2", 123},
        {"2", "1", 2}
    };

    for(auto transaction_ : transactions) {
        bc.add_block(transaction_);
    }

    ASSERT_EQ(bc.size(), 3);

    auto blocks = bc.get_blocks();

    for(int i = 0; i < transactions.size(); i++) {
        ASSERT_EQ(blocks[i+1].get_data(), to_string(jsonify(transactions[i])));
    }
}
