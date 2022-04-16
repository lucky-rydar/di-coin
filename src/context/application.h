#pragma once

#include <memory>
#include <string>
#include <map>
#include <iostream>
#include <mutex>

#include <lrrp.h>

#include "core/blockchain.h"
#include "server/get_server_info_handler.h"

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

    server_info server_info_;
    unique_ptr<lrrp::server> server_;
    unique_ptr<std::thread> server_thread_;

    application();
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
    void exit();

    // this method should be called once in main
    void setup_server(int argc, char** argv);

    // methods for network interaction
    server_info get_peer_info(string ip, int port);
};
