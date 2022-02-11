#include "gtest/gtest.h"

#include <json.hpp>
#include <spdlog/spdlog.h>

using namespace nlohmann;

TEST(json, json1)
{
    json j = {{"value", 1}};
    ASSERT_EQ("{\"value\":1}", to_string(j));
}
