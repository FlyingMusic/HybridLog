#ifndef __HCONFIG_FACTORY__
#define __HCONFIG_FACTORY__

#include "hconfig.h"

class ConfigFactory {
public:
    static HybridConfig *getConfig(ConfigMode config_mode);
};
#endif
