#include "dlog.h"

int main() {
    set_log_level_file("asyn.log", LEVEL_DEBUG);
    LOG_DEBUG("hello world");
    close_log();
    return 0;
}
