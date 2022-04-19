#pragma once

#include <lrrp.h>
#include <spdlog/spdlog.h>

#include <config/peer_list_loader.h>
#include <context/application.h>
#include <core/block.h>
#include <optional>

using namespace std;

// this class takes list of peers and sends messages to all of them
class peers_sender
{
    vector<peer> peers_;
public:
    peers_sender(vector<peer> available_peers);

    void add_block(block block);
    void add_transaction(transaction transaction);
};
