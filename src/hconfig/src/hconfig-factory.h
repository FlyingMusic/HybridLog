#ifndef __HCONFIG_FACTORY__
#define __HCONFIG_FACTORY__

#include "hconfig.h"

class ConfigFactory {
public:
    static int setConfigFile(const char *config_path);
    static HybridConfig *getConfig(ConfigMode config_mode, const char *config_path = NULL);
private:
    static char m_configFile[1024];
};
#endif
