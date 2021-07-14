#include "hlog.h"

#define LOG_TEST_MODEL "TEST_MODEL"
int main() {
    set_log_mode(NORMAL_MODE);
    set_log_level_file("access.log", LEVEL_DEBUG, 10);
    set_log_level_file("access.log", LEVEL_ERROR, 10);
    set_log_level_file("access.log", LEVEL_INFO, 10);
    LOG_D(LOG_TEST_MODEL, "hello debug");
    LOG_I(LOG_TEST_MODEL, "hello info");
    LOG_E(LOG_TEST_MODEL, "hello error");
    close_log();
    return 0;
}
