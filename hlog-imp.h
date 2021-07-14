#ifndef _HYBRID_LOG_IMP_
#define _HYBRID_LOG_IMP_

#include <list>

#define NORMAL_LOG 0x01
#define ASYNC_LOG  0x02
#define NET_LOG    0x03

class LogWriter {
    virtual int openLog(const char *log_file);
    virtual int writeLog();
    virtual int closeLog();
};

class NormalLogWriter : public LogWriter {

};

class AsyncLogWriter : public LogWriter {

};

class NetLogWriter : public LogWriter {

};

class LogManager {
public:
    LogManager();
    ~LogManager();
    int addLogWriter();
    int removeLogWriter();
    int initLogWriter(const char* log_file, int log_level, int log_size);
    int dispatchLog(int log_level, const char *log_context);
    void closeLogWriter();
private:
    std::list<LogWriter *> m_logWriter;

};

#endif
