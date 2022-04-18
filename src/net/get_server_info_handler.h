#pragma once

#include <string>

#include <lrrp.h>
#include <nlohmann/json.hpp>

#include "context/application.h"

using namespace nlohmann;

class application;

class get_server_info_handler : public lrrp::handler_base
{
public:
    virtual lrrp::response handle(const lrrp::request& request) override;
};
