#include "get_server_info_handler.h"

lrrp::response get_server_info_handler::handle(const lrrp::request& request) {
    auto info = application::instance().get_server_info();

    json payload;
    payload["ip"] = info.ip;
    payload["port"] = info.port;

    return lrrp::response_builder().set_payload(payload).set_status(lrrp::status_type::ok).build();
}
