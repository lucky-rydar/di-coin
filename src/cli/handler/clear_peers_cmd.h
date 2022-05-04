#pragma once

#include <iostream>

#include "command_handler_base.h"
#include "context/application.h"

class clear_peers_cmd : public command_handler_base
{
public:
    void handle(vector<string>& params) override {
        auto& app = application::instance();
        app.get_config().get_peers().clear();
        cout << "Peers are cleared" << endl;
    }

    string name() override {
        return "clear_peers";
    }
};
