#include "gtest/gtest.h"

#include <config/config.h>

TEST(config, load_peers)
{
    // create file and load test peers
    ofstream file(peer_list_file);

    string ip = "127.0.0.1";
    string port1 = "99", port2 = "100";

    file << ip + ":" + port1 + "\n";
    file << ip + ":" + port2;
    file.close();

    // create config and load peers
    config c;
    c.load();
    ASSERT_EQ(c.get_peers().size(), 2);

    ASSERT_EQ(c.get_peers()[0].ip, ip);
    ASSERT_EQ(c.get_peers()[0].port, stoi(port1));

    remove(peer_list_file.c_str());
}

TEST(config, no_file_test)
{
    config c;
    c.load();
    ASSERT_EQ(c.get_peers().size(), 0);
}
