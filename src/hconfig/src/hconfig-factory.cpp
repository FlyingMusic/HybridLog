#include "hconfig-factory.h"
#include <string.h>


char ConfigFactory::m_configFile[1024] = {0};

int ConfigFactory::setConfigFile(const char *config_path) {
    if (NULL == config_path) {
        printf("config path is NULL in set config file\n");
        return -1;
    }
    strncpy(m_configFile, config_path, sizeof(m_configFile));
    return 0;
}
HybridConfig* ConfigFactory::getConfig(ConfigMode config_mode, const char *config_path) {
    HybridConfig *hconfig = NULL;
    switch (config_mode) {
        case NORMAL_LOG_MANAGER:
            hconfig = new NormalLogConfig();
            break;
        case ASYNC_LOG_MANAGER:
            hconfig = new AsyncLogConfig();
            break;
        case NET_LOG_MANAGER:
            hconfig = new NetLogConfig();
            break;
        case LOG_MANAGER_INIT:
            hconfig = new LogManagerInitConfig();
            break;
    }
    const char *config_file = config_path ? config_path : m_configFile;
    if (hconfig) {
        if (0 != hconfig->loadConfig(config_file)) {
            printf("load config failed in get config\n");
            delete hconfig;
            hconfig = NULL;
        }
    }
    return hconfig;
}
