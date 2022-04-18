#include "config.h"

config::config() {
    peer_list_loader_ = std::make_unique<peer_list_loader>(peer_list_file);
}

void config::load() {
    peer_list_loader_->load_peers();
}

vector<peer>& config::get_peers() {
    return peer_list_loader_->get_peers();
}
