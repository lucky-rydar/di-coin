#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <sstream>

#include "handler/command_handler_base.h"
#include "handler/echo_cmd.h"

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
