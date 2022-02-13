#include "gtest/gtest.h"

#include <utils/jsonifier.h>
#include <core/block.h>

TEST(block, block_jsonify)
{
    string data = "hello";
    string prev_hash = "prev hash";
    block b({"1", "2", 3}, prev_hash);

    auto jsoned = jsonify(b);

    ASSERT_EQ(jsoned["prev_hash"], prev_hash);
}
