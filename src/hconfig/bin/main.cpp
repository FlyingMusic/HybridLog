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
    //LogManagerInitConfig
    LogManagerInitConfig *init_config = dynamic_cast<LogManagerInitConfig*>(ConfigFactory::getConfig(LOG_MANAGER_INIT));
    if (NULL == init_config) {
        printf("get config failed!\n");
        return -1; 
    }
    printf("normal mode: %d\n", init_config->getNormalMode());
    printf("async mode: %d\n", init_config->getAsyncMode());
    printf("net mode: %d\n", init_config->getNetMode());
    delete init_config;

    //NormalLogConfig
    NormalLogConfig *normal_config = dynamic_cast<NormalLogConfig*>(ConfigFactory::getConfig(NORMAL_LOG_MANAGER));
    if (NULL == normal_config) {
        printf("get config failed!\n");
        return -1; 
    }
    printf("normal log size: %d\n", normal_config->getLogSize());
    printf("normal log level: %d\n", normal_config->getMaxLevel());
    printf("normal log valid: %d\n", normal_config->isOpen());
    printf("normal log debug: %s\n", normal_config->getDebugPath());
    printf("normal log info: %s\n", normal_config->getInfoPath());
    printf("normal log notice: %s\n", normal_config->getNoticePath());
    printf("normal log warn: %s\n", normal_config->getWarnPath());
    printf("normal log error: %s\n", normal_config->getErrorPath());
    delete normal_config;

    return 0;
}
