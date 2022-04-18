#pragma once

#include <memory>
#include <regex>

#include "peer_list_loader.h"

using namespace std;

const string peer_list_file = "peers.txt";

class config
{
    unique_ptr<peer_list_loader> peer_list_loader_;

public:
    config();

    void load();

    vector<peer>& get_peers();
};
