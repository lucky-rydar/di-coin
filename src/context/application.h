#pragma once

#include <memory>
#include <string>
#include <map>
#include <iostream>
#include <mutex>

#include <lrrp.h>
#include <spdlog/spdlog.h>

#include "core/blockchain.h"
#include "core/mempool.h"
#include "config/config.h"

#include "net/peers_sender.h"
#include "net/get_server_info_handler.h"
#include "net/add_peer_handler.h"
#include "net/get_block_handler.h"
#include "net/get_genesis_handler.h"
#include "net/peer_client.h"
#include "net/add_block_handler.h"
#include "net/add_transaction_handler.h"


using namespace std;

class invalid_transaction_exception : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid transaction";
    }
};

typedef map<string, int> accounts;

struct server_info
{
    string ip;
    int port;
};

class application
{
    accounts accounts_;
    blockchain blockchain_;
    mempool mempool_;
    config config_;

    server_info server_info_;
    unique_ptr<lrrp::server> server_;
    unique_ptr<std::thread> server_thread_;

    string miner_condition = "00000";
    miner miner_;

    application();

    // method is needed to notify about myself
    void notify_peer_about_me(peer p);
    void notify_peers_about_me();

    void sync_with_network();
public:
    /*
     * this mutex is needed to lock
     * command processing when server
     * does smth with context and when
     * cli wants to do smth it is locked
     * for server
     */
    mutex cli_server_turn;

    static application& instance() {
        static application instance;
        return instance;
    }

    void add_transaction(string from, string to, int amount);
    void emit_coins(string to, int amount);
    int get_balance(string account);
    vector<block> get_blocks();
    server_info get_server_info();
    void mine_block();
    bool add_peer_server_handler(peer p);
    bool add_peer_command_handler(peer p);
    void exit();

    mempool& get_mempool();
    blockchain& get_blockchain();
    config& get_config();

    // this methods should be called once in main
    void setup_server(int argc, char** argv);
    void setup_blockchain();

    // methods for network interaction
    server_info get_peer_info(string ip, int port);
    block get_block_by_prev_hash(string prev_hash);
    vector<peer> available_peers();

    void proceed_block(block b, bool validate = true);
};
