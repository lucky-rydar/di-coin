#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

struct peer
{
    string ip;
    int port;
};

class peer_list_loader
{
    string filename_;

    vector<peer> peers_;
public:
    peer_list_loader(std::string const& filename);

    void load_peers();

    vector<peer>& get_peers();
};
