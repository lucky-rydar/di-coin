#include "peer_list_loader.h"

peer_list_loader::peer_list_loader(std::string const& filename)
    : filename_(filename) {}

void peer_list_loader::load_peers() {
    peers_.clear();

    ifstream file(filename_);
    if(!file.is_open()) {
        return;
    }

    string line;
    while (getline(file, line)) {
        if(line != "") {
            regex re("([\\d\\.]+)\\:([1-9][\\d]*)");

            smatch match;
            if (regex_search(line, match, re)) {
                peer p;
                p.ip = match[1];
                p.port = stoi(match[2]);
                peers_.push_back(p);
            }
        }
    }
    file.close();
}

vector<peer>& peer_list_loader::get_peers() {
    return peers_;
}
