#include <iostream>

#include <cli/cli.h>

int main(int argc, char** argv) {
    application::instance().setup_server(argc, argv);
    application::instance().setup_blockchain();

    cli cli_;
    cli_.run();
    return 0;
}
