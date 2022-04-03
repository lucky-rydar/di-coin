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
    static transaction create(string from, string to, uint64_t amount);
    static transaction coinbase(string to, uint64_t amount);

    string from;
    string to;
    uint64_t amount;
};
