#pragma once

#include <lrrp.h>

#include <context/application.h>
#include <core/block.h>
#include <net/peers_sender.h>

class add_block_handler : public lrrp::handler_base
{
public:
    virtual lrrp::response handle(const lrrp::request& req) override;
};
