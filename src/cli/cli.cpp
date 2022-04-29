#include "cli.h"

cli::cli() {
    register_command_handler(make_unique<echo_cmd>());
    register_command_handler(make_unique<send_cmd>());
    register_command_handler(make_unique<emit_cmd>());
    register_command_handler(make_unique<balance_cmd>());
    register_command_handler(make_unique<blocks_cmd>());
    register_command_handler(make_unique<check_peer_cmd>());
    register_command_handler(make_unique<mine_cmd>());
}

void cli::register_command_handler(unique_ptr<command_handler_base> handler) {
    handlers.insert(make_pair(handler->name(), move(handler)));
}

void cli::run() {
    while(true) {
        cout << "> ";

        string input;
        getline(cin, input);
        trim(input);

        if (input == "exit") {
            application::instance().exit();
            break;
        }

        if (input.empty()) {
            continue;
        }

        vector<string> params;
        string command;
        stringstream ss(input);
        ss >> command;
        string param;
        while (ss >> param) {
            params.push_back(param);
        }

        auto it = handlers.find(command);
        if (it != handlers.end()) {
            try {
                it->second->handle(params);
            } catch (const std::exception& e) {
                cout << it->second->help() << endl;
            }
        } else {
            cout << "Unknown command: " << command << endl;
        }
    }
}

void cli::trim(string& input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}
