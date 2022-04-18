#include "get_block_handler.h"

lrrp::response get_block_handler::handle(const lrrp::request& request) {
    application& app = application::instance();
    app.cli_server_turn.lock();

    string block_hash = request.get_param<string>("block_hash");
    block block;
    json payload;
    try {
        block = app.get_blockchain().get_by_prev_hash(block_hash);
        payload["no-blocks"] = false;
        payload["block"] = jsonify(block);
    } catch (const std::exception& e) {
        payload["no-blocks"] = true;
    }

    app.cli_server_turn.unlock();

    return lrrp::response_builder().set_status(lrrp::status_type::ok).set_payload(payload).build();
}
