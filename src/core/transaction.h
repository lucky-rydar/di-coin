#pragma once

#include <string>

#include <json.hpp>
#include <utils/jsonifier.h>
#include <utils/crypto.h>

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
    static string sha256(transaction);

    static transaction from_json(json j) {
        transaction ret;
        ret.from = j["from"];
        ret.to = j["to"];
        ret.amount = j["amount"];
        return ret;
    }

    string from;
    string to;
    uint64_t amount;
};
