#pragma once

#include <context/application.h>

#include "command_handler_base.h"

class mine_cmd : public command_handler_base
{
    void handle(vector<string>& params) override {
        if (params.size() != 1) {
            throw invalid_argument("Invalid number of arguments");
        }

        int amount_of_blocks = stoi(params[0]);
        if(application::instance().get_mempool().size() < amount_of_blocks) {
            throw invalid_argument("Not enough transactions in mempool");
        }

        for(int i = 0; i < amount_of_blocks; i++) {
            application::instance().mine_block();
        }
    }

    string name() override {
        return "mine";
    }
};
