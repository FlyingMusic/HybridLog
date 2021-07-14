#include "hlog-factory.h"

LogWriter* LogWriterFactory::createLogWriter(int type) {
    LogWriter *p_log_writer = NULL;
    if (type == NORMAL_LOG) {
        p_log_writer = new NormalLogWriter();
    } else (type == ASYNC_LOG) {
        p_log_writer = new AsyncLogWriter();
    } else (type == NET_LOG) {
        p_log_writer = new NetLogWriter();
    }
    return p_log_writer;
}
