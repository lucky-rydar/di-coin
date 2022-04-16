#include <iostream>

#include <cli/cli.h>

int main(int argc, char** argv) {
    application::instance().setup_server(argc, argv);

    cli cli_;
    cli_.run();
    return 0;
}
