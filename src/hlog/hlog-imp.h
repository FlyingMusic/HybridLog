#ifndef _HYBRID_LOG_IMP_
#define _HYBRID_LOG_IMP_

#include <list>
#include <map>
#include <string.h>
#include "ThreadPool.h"
#include "concurrent_queue.h"

#define NORMAL_LOG 0x01
#define ASYNC_LOG  0x02
#define NET_LOG    0x03

class LogWriter {
public:
    LogWriter() {}
    virtual ~LogWriter() {}
    virtual int init(const LogConfig *log_config = NULL);
    virtual int write(int log_level, const char *log_context);
    virtual void close();
protected:
    std::map<int, int> m_level2fd;
    LogConfig *m_logConfig;
};

class NormalLogWriter : public LogWriter {
public:
    virtual int init(const LogConfig *log_config);
    virtual int write(int log_level, const char *log_context);
    virtual void close();
};

class AsyncLogWriter : public LogWriter {
public:
    AsyncLogWriter();
    ~AsyncLogWriter();
    virtual int init(const LogConfig *log_config);
    virtual int write(int log_level, const char *log_context);
    virtual void close();
    void threadFunc();
    class async_log_st{
    public:
        int log_level; 
        char log_context[1024];
        async_log_st() : log_level(0){
            memset(log_context, 0, sizeof(log_context)); 
        }
        bool operator<(const async_log_st& other) const {
            return  this->log_level < other.log_level;
        }
    };
private:
    bool m_isFinish;
    ThreadPool *m_threadPool;
    concurrent_queue<async_log_st> m_queue;
};

class NetLogWriter : public LogWriter {
public:
    virtual int init(const LogConfig *log_config);
    virtual int write(int log_level, const char *log_context);
    virtual void close();
};

class LogManager {
public:
    LogManager();
    ~LogManager();
    int loadConfig(const char *conf_path);
    LogConfig* getLogConfig();
    int addLogWriter(int log_mode);
    int removeLogWriter(int log_mode);
    int initLogWriter(const LogConfig *log_config);
    void dispatchLog(int log_level, const char *log_context);
    void closeLogWriter();
    typedef std::map<int, LogWriter *>::iterator mapIter;
private:
    std::map<int, LogWriter *> m_logWriter;
    LogConfig *m_logConfig;
};

#endif
