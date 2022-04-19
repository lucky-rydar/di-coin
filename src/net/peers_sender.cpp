#include "peers_sender.h"

peers_sender::peers_sender(vector<peer> available_peers) {
    peers_ = available_peers;
}

void peers_sender::add_block(block block) {
    for (auto& peer : peers_) {
        lrrp::client client_(peer.ip, peer.port);

        lrrp::request req = lrrp::request_builder("add_block")
            .set_param("block", jsonify(block).dump())
            .build();

        client_.send(req);
    }
}

void peers_sender::add_transaction(transaction transaction) {
    // may be this functions is useless
}
