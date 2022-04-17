#include "application.h"

application::application() : miner_(miner_condition) {
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

    transaction t = transaction::create(from, to, amount);
    mempool_.push(t);
}

void application::emit_coins(string to, int amount) {
    if(amount <= 0) {
        throw invalid_transaction_exception();
    }

    transaction t = transaction::coinbase(to, amount);
    mempool_.push(t);
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

void application::mine_block() {
    auto tx = mempool_.pop();

    if(accounts_.find(tx.from) == accounts_.end()) {
        accounts_[tx.from] = 0;
    }

    if(accounts_.find(tx.to) == accounts_.end()) {
        accounts_[tx.to] = 0;
    }

    if(tx.amount > accounts_[tx.from] && tx.from != "") {
        spdlog::error("Invalid transaction, account do not have enough money");
        // maybe need to notify peers about that
    } else {
        block b(tx, blockchain_.get_blocks().back().get_hash());
        miner_.mine(b);
        blockchain_.add_block(b);

        if(tx.from != "")
            accounts_[tx.from] -= tx.amount;
        accounts_[tx.to] += tx.amount;
    }
}

void application::exit() {
    server_->stop();
}

mempool& application::get_mempool() {
    return mempool_;
}
