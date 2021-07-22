#include "hconfig-factory.h"

HybridConfig* ConfigFactory::getConfig(ConfigMode config_mode) {
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
    return hconfig;
}
