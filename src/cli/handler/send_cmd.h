#pragma once

#include "command_handler_base.h"

#include <context/application.h>

class send_cmd : public command_handler_base
{
public:
    void handle(vector<string>& params) override {
        if (params.size() != 3) {
            throw invalid_argument("Invalid number of arguments");
        }
        application::instance().add_transaction(params[0], params[1], stoi(params[2]));
    }

    string name() override {
        return "send";
    }
};
