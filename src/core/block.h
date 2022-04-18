#pragma once
#include <chrono>

#include <utils/crypto.h>
#include <utils/jsonifier.h>
#include <utils/time_utils.h>
#include <spdlog/spdlog.h>

#include "transaction.h"
#include "miner.h"

namespace tu = time_utils;

class block
{
    template <Jsonifiable T>
    friend json jsonify(T&);

private:
    string timestamp;
    transaction transaction_;
    string prev_hash;
    string hash;
    uint64_t nonce;

    void gen_timestamp();
    void actualize();

    json jsonify();
public:
    block() {}
    block(transaction transaction_, string prev_hash);

    void operator=(const block& b);

    string gen_hash();
    string get_hash();
    string get_prev_hash();
    string get_timestamp();
    string get_data();
    transaction get_transaction();
    void set_nonce(uint64_t nonce);

    static block from_json(json j) {
        block ret;
        ret.timestamp = j["timestamp"];
        ret.transaction_ = transaction::from_json(j["transaction"]);
        ret.prev_hash = j["prev_hash"];
        ret.hash = j["hash"];
        ret.nonce = j["nonce"];
        return ret;
    }
};
