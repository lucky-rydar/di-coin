#pragma once

#include <iostream>

#include "command_handler_base.h"

class peers_cmd : public command_handler_base
{
public:
    void handle(vector<string>& params) override {
        auto& app = application::instance();
        auto& peers = app.get_config().get_peers();
        for (auto& peer : peers) {
            cout << peer.ip << ":" << peer.port << endl;
        }
    }

    string name() override {
        return "peers";
    }
};
