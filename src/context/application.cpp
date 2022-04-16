#include "application.h"

application::application() {
    blockchain_.genesis();
}

void application::setup_server(int argc, char** argv) {
    if(argc != 3) {
        cout << "Usage: ./" << argv[0] << " <ip> <port>" << endl;
        throw std::invalid_argument("Invalid number of arguments");
    }

    server_info_.ip = argv[1];
    server_info_.port = stoi(argv[2]);

    server_ = std::make_unique<lrrp::server>(server_info_.port);

    server_->add_handler("get_server_info", make_unique<get_server_info_handler>());

    server_thread_ = std::make_unique<std::thread>([this]() {
        try {
            server_->run_async();
            puts("Server ended");
        } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    });
    server_thread_->detach();
}

void application::add_transaction(string from, string to, int amount) {
    if(amount <= 0) {
        throw invalid_transaction_exception();
    }

    if(accounts_.find(from) == accounts_.end()) {
        accounts_[from] = 0;
    }

    if(accounts_.find(to) == accounts_.end()) {
        accounts_[to] = 0;
    }

    if(accounts_[from] < amount) {
        throw invalid_transaction_exception();
    }

    blockchain_.add_transaction(transaction::create(from, to, amount));
    accounts_[from] -= amount;
    accounts_[to] += amount;
}

void application::emit_coins(string to, int amount) {
    if(amount <= 0) {
        throw invalid_transaction_exception();
    }

    if(accounts_.find(to) == accounts_.end()) {
        accounts_[to] = 0;
    }

    blockchain_.add_transaction(transaction::coinbase(to, amount));
    accounts_[to] += amount;
}

int application::get_balance(string account) {
    if(accounts_.find(account) == accounts_.end()) {
        return 0;
    }

    return accounts_[account];
}

vector<block> application::get_blocks() {
    return blockchain_.get_blocks();
}

server_info application::get_server_info() {
    return server_info_;
}

server_info application::get_peer_info(string ip, int port) {
    lrrp::client c(ip, port);
    lrrp::request req = lrrp::request_builder("get_server_info").build();
    lrrp::response res = c.send(req);

    server_info info;
    info.ip = res.get_payload()["ip"];
    info.port = res.get_payload()["port"];

    return info;
}

void application::exit() {
    server_->stop();
}
