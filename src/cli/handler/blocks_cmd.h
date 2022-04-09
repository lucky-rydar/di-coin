#pragma once

#pragma once

#include <iostream>

#include <fort.hpp>

#include "command_handler_base.h"
#include <context/application.h>

using namespace std;
using namespace fort;

class blocks_cmd : public command_handler_base
{
public:
    void handle(vector<string>& params) override {
        auto app = application::instance();
        auto blocks = app.get_blocks();
        for(auto& b : blocks) {
            char_table table;
            table << fort::header
                << "" << "Block" << fort::endr
                << "timestamp" << b.get_timestamp() << fort::endr
                << "data" << b.get_data() << fort::endr
                << "hash" << b.get_hash() << fort::endr
                << "previous hash" << b.get_prev_hash() << fort::endr;

            cout << table.to_string() << endl;
        }
    }

    string name() override {
        return "blocks";
    }
};
