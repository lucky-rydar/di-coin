#include "get_genesis_handler.h"

lrrp::response get_genesis_handler::handle(const lrrp::request& request) {
    application& app = application::instance();
    app.cli_server_turn.lock();

    auto block = app.get_blockchain().get_genesis_block();

    app.cli_server_turn.unlock();

    json payload;
    payload["block"] = jsonify(block);

    return lrrp::response_builder().set_status(lrrp::status_type::ok).set_payload(payload).build();
}
