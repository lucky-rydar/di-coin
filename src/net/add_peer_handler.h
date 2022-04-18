#pragma once

#include <lrrp.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "context/application.h"

using namespace nlohmann;

class add_peer_handler : public lrrp::handler_base
{
public:
    virtual lrrp::response handle(const lrrp::request& request) override;
};
