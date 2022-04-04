#include "echo_cmd.h"

echo_cmd::echo_cmd() {

}

void echo_cmd::handle(vector<string>& params) {
    for (auto& param : params) {
        cout << param << " ";
    }
    cout << endl;
}

string echo_cmd::name() {
    return "echo";
}
