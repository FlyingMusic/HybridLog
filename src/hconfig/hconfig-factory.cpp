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
        case NORMAL_LOG_MANAGER:
            hconfig = new NetLogConfig();
            break;
    }
    return hconfig;
}
