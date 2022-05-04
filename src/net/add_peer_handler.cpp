#include "add_peer_handler.h"

lrrp::response add_peer_handler::handle(const lrrp::request& request) {
    application& app = application::instance();
    app.cli_server_turn.lock();

    string ip = request.get_param<string>("ip");
    int port = request.get_param<int>("port");

    if(std::count_if(
            app.get_config().get_peers().begin(),
            app.get_config().get_peers().end(),
            [ip, port](const peer& p) {
                return p.ip == ip && p.port == port;
            }) == 0) {
        auto peer_info = app.get_peer_info(ip, port);
        if(peer_info.port != -1) {
            app.add_peer_server_handler({ip, port});
        }

        app.cli_server_turn.unlock();
    }

    return lrrp::response_builder().set_status(lrrp::status_type::ok).build();
}
