#pragma once

#include <iostream>

#include "command_handler_base.h"
#include "context/application.h"

class add_peer_cmd : public command_handler_base
{
public:
    void handle(vector<string>& params) override {
        if (params.size() != 2) {
            throw invalid_argument("Invalid number of arguments");
        }

        auto& app = application::instance();
        if(app.add_peer_command_handler({params[0], stoi(params[1])})) {
            cout << "Added peer " << params[0] << ":" << params[1] << endl;
        } else {
            cout << "Peer cant be reached" << endl;
        }
    }

    string name() override {
        return "add_peer";
    }
};
