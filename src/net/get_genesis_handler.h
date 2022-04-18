#pragma once

#include <lrrp.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "context/application.h"

using namespace nlohmann;

class get_genesis_handler : public lrrp::handler_base
{
public:
    lrrp::response handle(const lrrp::request& request);
};

