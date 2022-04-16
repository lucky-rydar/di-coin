#pragma once

#include <lrrp.h>

#include "command_handler_base.h"
#include <context/application.h>

class check_peer_cmd : public command_handler_base
{
public:
    void handle(vector<string>& params) override {
        if(params.size() != 2) {
            cout << "Usage: check_peer <ip> <port>" << endl;
            throw invalid_argument("Invalid number of arguments");
        }

        string ip = params[0];
        int port = stoi(params[1]);
        server_info info;
        try {
            info = application::instance().get_peer_info(ip, port);
        } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }

        cout << "The information about peer: { " << info.ip << ":" << info.port << " }" << endl;
    }

    string name() override {
        return "check_peer";
    }
};
