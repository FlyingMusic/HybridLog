#ifndef _HYBRID_LOG_IMP_
#define _HYBRID_LOG_IMP_

#include <list>
#include <map>
#include <string.h>
#include "ThreadPool.h"
#include "concurrent_queue.h"

typedef enum {
    NORMAL_MODE = 0x0,
    ASYNC_MODE,
    NET_MODE,
} LogMode;

class LogWriter {
public:
    LogWriter() {}
    virtual ~LogWriter() {}
    virtual int init(const char *config_file = NULL);
    virtual int write(int log_level, const char *log_context);
    virtual void close();
protected:
    std::map<int, int> m_level2fd;
    LogMode m_logMode;
};

class NormalLogWriter : public LogWriter {
public:
    NormalLogWriter(){ }
    virtual int init(const char *config_file);
    virtual int write(int log_level, const char *log_context);
    virtual void close();
};

class AsyncLogWriter : public LogWriter {
public:
    AsyncLogWriter();
    ~AsyncLogWriter();
    virtual int init(const char *config_file);
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
    NetLogWriter();
    virtual int init(const char *config_path);
    virtual int write(int log_level, const char *log_context);
    virtual void close();
};

class LogManager {
public:
    LogManager();
    ~LogManager();
    int init(const char *conf_path);
    int addLogWriter(LogMode log_mode);
    int removeLogWriter(int log_mode);
    int initLogWriter();
    void dispatchLog(int log_level, const char *log_context);
    void closeLogWriter();
    typedef std::map<int, LogWriter *>::iterator mapIter;
private:
    std::map<int, LogWriter *> m_logWriter;
};

#endif
