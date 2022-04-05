#pragma once

#include "command_handler_base.h"

#include <context/application.h>

class emit_cmd : public command_handler_base
{
public:
    void handle(vector<string>& params) override {
        if (params.size() != 2) {
            throw invalid_argument("Invalid number of arguments");
        }
        application::instance().emit_coins(params[0], stoi(params[1]));
    }

    string name() override {
        return "emit";
    }
};
