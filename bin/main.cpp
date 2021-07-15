#include "hlog.h"
#include <time.h>    
#include <stdio.h>    
#include "Config.h"

#define LOG_TEST_MODEL "TEST_MODEL"

int main() {
    Config *p_config = new Config();
    delete p_config;
    p_config = NULL;
#if 0
    set_log_mode(NORMAL_MODE);
    set_log_level_file("normal.log", LEVEL_DEBUG, 10);
    set_log_level_file("normal.log", LEVEL_ERROR, 10);
    set_log_level_file("normal.log", LEVEL_INFO, 10);
    clock_t start = clock(); 
    for (int i = 0; i < 1000000; ++i) {
        LOG_D(LOG_TEST_MODEL, "hello debug");
        LOG_I(LOG_TEST_MODEL, "hello info");
        LOG_E(LOG_TEST_MODEL, "hello error");
    }
    clock_t end = clock();
    
    double costtime = (double)(end-start) / CLOCKS_PER_SEC;
    printf("normal time cost: %lf\n", costtime);
#endif 
    set_log_mode(ASYNC_MODE);
    set_log_level_file("async.log", LEVEL_DEBUG, 10);
    set_log_level_file("async.log", LEVEL_ERROR, 10);
    set_log_level_file("async.log", LEVEL_INFO, 10);
    clock_t start = clock(); 
    for (int i = 0; i < 1000000; ++i) {
        LOG_D(LOG_TEST_MODEL, "hello debug");
        LOG_I(LOG_TEST_MODEL, "hello info");
        LOG_E(LOG_TEST_MODEL, "hello error");
    }
    clock_t end = clock();
    double costtime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("async time cost: %lf\n", costtime);
    close_log();
    return 0;
}
