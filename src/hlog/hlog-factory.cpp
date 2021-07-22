#include <stdio.h>
#include "hlog-factory.h"

LogWriter* LogWriterFactory::createLogWriter(LogMode mode) {
    LogWriter *p_log_writer = NULL;
    switch (mode) {
        case NORMAL_MODE:
            p_log_writer = new NormalLogWriter();
            break;
        case ASYNC_MODE:
            p_log_writer = new AsyncLogWriter();
            break;
        case NET_MODE:
            p_log_writer = new NetLogWriter();
            break;
    }
    return p_log_writer;
}
