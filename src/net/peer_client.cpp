#include "peer_client.h"

peer_client::peer_client(peer p) : peer_(p) {}

optional<block> peer_client::get_block_by_prev_hash(string last_block_hash) {
    lrrp::client client_(peer_.ip, peer_.port);

    lrrp::request req = lrrp::request_builder("get_block")
        .set_param("block_hash", last_block_hash)
        .build();

    lrrp::response resp = client_.send(req);

    if(resp.get_payload()["no-blocks"] == false) {
        return block::from_json(resp.get_payload()["block"]);
    } else {
        return {};
    }
}

block peer_client::get_genesis_block() {
    lrrp::client client_(peer_.ip, peer_.port);
    lrrp::request req = lrrp::request_builder("get_genesis").build();

    auto resp = client_.send(req);

    return block::from_json(resp.get_payload()["block"]);
}
