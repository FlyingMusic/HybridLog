#ifndef _HYBRID_LOG_FACTORY_
#define _HYBRID_LOG_FACTORY_

#include "hlog-imp.h"

class LogWriterFactory {
public:
    static int setDefaultConfig(const char *config_path);
    static LogWriter *createLogWriter(LogMode mode);
private:
    char defaut_config[1024];
};
#endif
