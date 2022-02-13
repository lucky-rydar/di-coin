#pragma once

#include <string>

#include <json.hpp>
#include <utils/jsonifier.h>

using namespace std;
using namespace nlohmann;

class transaction
{
    template <Jsonifiable T>
    friend json jsonify(T&);

private:
    json jsonify();

public:
    string from;
    string to;
    uint64_t amount;
};
