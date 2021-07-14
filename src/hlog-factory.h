#ifndef _HYBRID_LOG_FACTORY_
#define _HYBRID_LOG_FACTORY_

#include "hlog-imp.h"

class LogWriterFactory {
    static LogWriter *createLogWriter(int type);
};
#endif
