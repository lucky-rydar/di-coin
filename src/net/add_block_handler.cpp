#include "add_block_handler.h"

lrrp::response add_block_handler::handle(const lrrp::request& req) {
    puts("add_block_handler::handle");
    block b = block::from_json(json::parse(req.get_param<string>("block")));

    if(!application::instance().get_blockchain().has_block(b.get_hash())) {
        application::instance().proceed_block(b, true);

        auto peers = application::instance().available_peers();
        peers_sender(peers).add_block(b);
    }

    return lrrp::response_builder().set_status(lrrp::status_type::ok).build();
}
