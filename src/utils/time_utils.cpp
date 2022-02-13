#include "time_utils.h"

string time_utils::timestamp() {
    chrono::milliseconds timestamp =
        chrono::duration_cast<chrono::milliseconds>(
        chrono::system_clock::now().time_since_epoch()
    );
    return to_string(timestamp.count());
}
