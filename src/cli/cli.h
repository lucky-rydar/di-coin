#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <sstream>

#include "handler/command_handler_base.h"
#include "handler/echo_cmd.h"
#include "handler/send_cmd.h"
#include "handler/emit_cmd.h"
#include "handler/balance_cmd.h"
#include "handler/blocks_cmd.h"
#include "handler/check_peer_cmd.h"
#include "handler/mine_cmd.h"
#include "handler/add_peer_cmd.h"
#include "handler/peers_cmd.h"
#include "handler/clear_peers_cmd.h"

using namespace std;

class cli
{
    map<string, unique_ptr<command_handler_base>> handlers;

    void register_command_handler(unique_ptr<command_handler_base> handler);
    void trim(string& str);
public:
    cli();
    void run();
};
