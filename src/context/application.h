#pragma once

#include <memory>

using namespace std;

class application
{
    application();
public:
    static application instance() {
        static application instance;
        return instance;
    }
};
