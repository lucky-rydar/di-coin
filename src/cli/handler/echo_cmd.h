#pragma once

#include <iostream>

#include "command_handler_base.h"

using namespace std;

class echo_cmd : public command_handler_base
{
public:
    echo_cmd();
    void handle(vector<string>& params) override;
    string name() override;
};
