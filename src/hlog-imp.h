#ifndef _HYBRID_LOG_IMP_
#define _HYBRID_LOG_IMP_

#include <list>
#include <map>

#define NORMAL_LOG 0x01
#define ASYNC_LOG  0x02
#define NET_LOG    0x03

class LogWriter {
public:
    virtual int init(const char *log_file, int log_level, int log_size);
    virtual int write(int log_level, const char *log_context);
    virtual void close();
protected:
    std::map<int, int> m_level2fd;
};

class NormalLogWriter : public LogWriter {
public:
    virtual int init(const char *log_file, int log_level, int log_size);
    virtual int write(int log_level, const char *log_context);
    virtual void close();
};

class AsyncLogWriter : public LogWriter {
public:
    virtual int init(const char *log_file, int log_level, int log_size);
    virtual int write(int log_level, const char *log_context);
    virtual void close();
};

class NetLogWriter : public LogWriter {
public:
    virtual int init(const char *log_file, int log_level, int log_size);
    virtual int write(int log_level, const char *log_context);
    virtual void close();
};

class LogManager {
public:
    LogManager();
    ~LogManager();
    int addLogWriter(int log_mode);
    int removeLogWriter(int log_mode);
    int initLogWriter(const char* log_file, int log_level, int log_size);
    void dispatchLog(int log_level, const char *log_context);
    void closeLogWriter();
    typedef std::map<int, LogWriter *>::iterator mapIter;
private:
    std::map<int, LogWriter *> m_logWriter;

};

#endif
