#include "hlog.h"
#include <time.h>    
#include <stdio.h>    
#include <getopt.h>
#include "Config.h"

#define LOG_TEST_MODEL "TEST_MODEL"

const char* const short_options = "c:";
struct option long_options[] = {
    {"config", 1, NULL, 'c'},
    {0, 0, 0, 0},
};

void Usage(const char *prog){
    printf("Usage: %s -c ./log.config\n",prog);
    return;
}
int main(int argc, char *argv[]) {
    const char *config_path = NULL;
    char c = 0;
    while((c = getopt_long (argc, argv, short_options, long_options, NULL)) != -1 && c != 255){
        switch (c){
            case 'c':
                config_path = optarg;
                break;
            case 'v':
            case 'h':
            case '?':
                Usage(argv[0]);
                exit(0);
        }
    }
    if (NULL == config_path) {
        Usage(argv[0]);
        return 0;
    }

    Config *config = new Config();
    config->load(config_path);
    char debug_path[512] = {0};
    int log_size = 0;
    config->GetString("DEBUG_LOG_PATH", debug_path, "DEBUG_LOG_PATH");
    config->GetValue("LOG_SIZE", log_size, 10);
    delete config;
    config = NULL;
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
    hlog_init(config_path);
#if 0
    set_log_mode(ASYNC_MODE);
    set_log_level_file("async.log", LEVEL_DEBUG, 10);
    set_log_level_file("async.log", LEVEL_ERROR, 10);
    set_log_level_file("async.log", LEVEL_INFO, 10);
#endif
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
