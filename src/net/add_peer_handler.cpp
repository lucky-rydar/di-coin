#include "add_peer_handler.h"

lrrp::response add_peer_handler::handle(const lrrp::request& request) {
    application& app = application::instance();
    app.cli_server_turn.lock();

    string ip = request.get_param<string>("ip");
    int port = request.get_param<int>("port");

    auto peer_info = app.get_peer_info(ip, port);
    if(peer_info.port != -1) {
        app.add_peer({ip, port});
    }

    app.cli_server_turn.unlock();

    return lrrp::response_builder().set_status(lrrp::status_type::ok).build();
}
