#include "hconfig-factory.h"
#include <stdio.h>

void Usage(const char *prog){
    printf("Usage: %s ./log.config\n",prog);
    return;
}

int main(int argc, char *argv[]) {
    if(argc < 2){
        Usage(argv[0]);
        return -1;
    }

    int ret = ConfigFactory::setConfigFile(argv[1]);
    if (0 != ret) {
        printf("set config file[%s] failed!\n", argv[1]);
        return -1;
    }
    LogManagerInitConfig *init_config = (LogManagerInitConfig*)ConfigFactory::getConfig(LOG_MANAGER_INIT);
    if (NULL == init_config) {
        printf("get config failed!\n");
        return -1; 
    }
    printf("normal mode: %d\n", init_config->getNormalMode());
    printf("async mode: %d\n", init_config->getAsyncMode());
    printf("net mode: %d\n", init_config->getNetMode());
    delete init_config;
    return 0;
}
