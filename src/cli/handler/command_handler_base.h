#pragma once

#include <vector>
#include <string>

using namespace std;

class command_handler_base
{
public:
    command_handler_base() {}
    virtual ~command_handler_base() {}
    virtual void handle(vector<string>& params) = 0;
    virtual string name() = 0;
};
