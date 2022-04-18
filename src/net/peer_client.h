#pragma once

#include <lrrp.h>
#include <spdlog/spdlog.h>

#include <config/peer_list_loader.h>
#include <context/application.h>
#include <core/block.h>
#include <optional>

using namespace std;

class peer_client
{
    peer peer_;
public:
    peer_client(peer p);

    optional<block> get_block_by_prev_hash(string last_block_hash);
    block get_genesis_block();
};
