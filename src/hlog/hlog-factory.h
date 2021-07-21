#ifndef _HYBRID_LOG_FACTORY_
#define _HYBRID_LOG_FACTORY_

#include "hlog-imp.h"

class LogWriterFactory {
public:
    static LogWriter *createLogWriter(LogMode mode);
};
#endif
