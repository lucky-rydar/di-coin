#pragma once

#include <string>

#include <lrrp.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <utils/jsonifier.h>

#include <context/application.h>

using namespace std;

class get_block_handler : public lrrp::handler_base
{
public:
    virtual lrrp::response handle(const lrrp::request& request) override;
};
