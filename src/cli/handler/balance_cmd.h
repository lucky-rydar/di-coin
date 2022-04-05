#pragma once

#include "command_handler_base.h"

#include <context/application.h>

class balance_cmd : public command_handler_base
{
public:
    void handle(vector<string>& params) override {
        if (params.size() != 1) {
            throw invalid_argument("Invalid number of arguments");
        }
        cout << application::instance().get_balance(params[0]) << endl;
    }

    string name() override {
        return "balance";
    }
};
