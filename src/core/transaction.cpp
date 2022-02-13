#include "transaction.h"

json transaction::jsonify() {
    json ret = {
        {"from", from},
        {"to", to},
        {"amount", amount}
    };
    return ret;
}
