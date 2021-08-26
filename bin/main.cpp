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

    int ret = hlog_init(config_path);
    if (0 != ret) {
        printf("hlog init failed!!\n");
        return -1;
    }
    printf("hlog init success!!\n");
    
    clock_t start = clock(); 
    for (int i = 0; i < 1000000; ++i) {
        LOG_D(LOG_TEST_MODEL, "hello debug");
        LOG_I(LOG_TEST_MODEL, "hello info");
        LOG_E(LOG_TEST_MODEL, "hello error");
    }
    clock_t end = clock();
    double costtime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("async time cost: %lf\n", costtime);
    hlog_close();
    return 0;
}
