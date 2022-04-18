#include "application.h"

application::application() : miner_(miner_condition) {
    config_.load();

    // here we check if network exists
    if(available_peers().size() > 0) {
        notify_peers_about_me();
        spdlog::info("Notified peers about me");
        // here we should sync with netwok
        sync_with_network();
    } else {
        // here init our own blockchain
        blockchain_.genesis();
    }
}

void application::notify_peers_about_me() {
    for(auto& peer : available_peers()) {
        lrrp::client client_(peer.ip, peer.port);
        lrrp::request req = lrrp::request_builder("add_peer")
                .set_param("ip", peer.ip)
                .set_param("port", peer.port)
                .build();

        client_.send(req);
    }
}

void application::sync_with_network() {
    auto p = available_peers()[rand() % available_peers().size()];
    peer_client pc(p);

    blockchain_.add_block(pc.get_genesis_block());

    while(true) {
        auto hash = blockchain_.get_last_block().get_hash();
        auto b = pc.get_block_by_prev_hash(hash);
        if(b.has_value()) {
            proceed_block(b.value(), false);
        } else {
            break;
        }
    }
}

void application::proceed_block(block b, bool validate) {
    auto t = b.get_transaction();

    if(validate) {
        if(t.amount > accounts_[t.from] || t.amount < 0) {
            throw invalid_transaction_exception();
        }
    }

    accounts_[t.from] -= t.amount;
    accounts_[t.to] += t.amount;

    blockchain_.add_block(b);
}

blockchain& application::get_blockchain() {
    return blockchain_;
}

config& application::get_config() {
    return config_;
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
    server_->add_handler("add_peer", make_unique<add_peer_handler>());
    server_->add_handler("get_block", make_unique<get_block_handler>());
    server_->add_handler("get_genesis", make_unique<get_genesis_handler>());

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

    server_info info{"", -1};
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

void application::add_peer(peer p) {
    auto res = get_peer_info(p.ip, p.port);
    if(res.port == -1) {
        return;
    }

    config_.get_peers().push_back(p);
}

vector<peer> application::available_peers() {
    vector<peer> ret;
    for(auto& peer : config_.get_peers()) {
        auto res = get_peer_info(peer.ip, peer.port);
        if(res.port != -1) {
            ret.push_back(peer);
        }
    }
    return ret;
}
