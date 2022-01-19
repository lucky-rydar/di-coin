#include "gtest/gtest.h"
#include "spdlog/spdlog.h"

#include "utils/crypto.h"
#include "utils/time_utils.h"

TEST(utils, sha256)
{
    auto hash1 = crypto::sha256("Hello");
    auto hash2 = crypto::sha256("World");

    ASSERT_EQ(hash1.length()/2, SHA256_DIGEST_LENGTH);
    ASSERT_EQ(hash2.length()/2, SHA256_DIGEST_LENGTH);

    ASSERT_NE(hash1, hash2);
}

TEST(utils_time, timestamp)
{
    namespace tu = time_utils;
    string t;
    ASSERT_NO_THROW(t = tu::timestamp());
    spdlog::info(t);
}