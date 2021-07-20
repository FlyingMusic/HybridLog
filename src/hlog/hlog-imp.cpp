#include "hlog-imp.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "utility.h"
#include "hlog-factory.h"
#include "ThreadPool.h"


using namespace std;

int LogWriter::init(const LogConfig *log_config) {
    return 0;
}
int LogWriter::write(int log_level, const char *log_context) {
    return 0;
}
void LogWriter::close() {
}


int NormalLogWriter::init(const LogConfig *log_config) {
    m_logConfig = log_config;

    if (false == createDirectory(log_file)) {
        printf("create directory[%s] error in normal log writer\n", log_file);
        return -1;
    }
    int fd = open(log_file, O_CREAT | O_RDWR | O_APPEND);
    if (fd < 0) {
        printf("open file[%s] error: %s\n", log_file, strerror(errno));
        return -1;
    }
    m_level2fd[log_level] = fd;
    return 0;
}
int NormalLogWriter::write(int log_level, const char *log_context) {
    map<int, int>::iterator iter = m_level2fd.find(log_level);
    if (iter == m_level2fd.end()) {
        printf("no logfile corresponding to level[%d]\n", log_level);
        return -1;
    }
    if (iter->second < 0) {
        printf("fd is invalid for level[%d]\n", log_level);
        return -1;
    }

    ::write(iter->second, (void *)log_context, strlen(log_context)); //ignore all error
    return 0;
}
void NormalLogWriter::close() {
     map<int, int>::iterator iter;
     for (iter = m_level2fd.begin(); iter != m_level2fd.end(); ++iter) {
        ::close(iter->second); 
        iter->second = -1;
     }
}


AsyncLogWriter::AsyncLogWriter() {
    m_threadPool = NULL;
    m_isFinish = false;
}

AsyncLogWriter::~AsyncLogWriter() {
    if (m_threadPool) {
        delete m_threadPool;
        m_threadPool = NULL;
    }
}

void* thread_func(void *arg);

int AsyncLogWriter::init(const LogConfig *log_config) {
    if (false == createDirectory(log_file)) {
        printf("create directory[%s] error in normal log writer\n", log_file);
        return -1;
    }
    int fd = open(log_file, O_CREAT | O_RDWR | O_APPEND);
    if (fd < 0) {
        printf("open file[%s] error: %s\n", log_file, strerror(errno));
        return -1;
    }
    m_level2fd[log_level] = fd;

    if (NULL == m_threadPool) {
        m_threadPool = new ThreadPool(1, (ThreadPoolCallback)thread_func, (void *)this);
        m_threadPool->start();
    }
    return 0;
}
void* thread_func(void *arg) {
    AsyncLogWriter *async_log_writer = (AsyncLogWriter*)arg;
    async_log_writer->threadFunc();
    return NULL;
}

void AsyncLogWriter::threadFunc() {
    //while (!m_isFinish || !m_queue.empty()) {
    while (!m_isFinish) {
        async_log_st log_st = m_queue.wait_and_pop();

        map<int, int>::iterator iter = m_level2fd.find(log_st.log_level);
        if (iter == m_level2fd.end()) {
            printf("no logfile corresponding to level[%d]\n", log_st.log_level);
        }
        if (iter->second < 0) {
            printf("fd is invalid for level[%d]\n", log_st.log_level);
        }

        ::write(iter->second, (void *)log_st.log_context, strlen(log_st.log_context));
    }
}
int AsyncLogWriter::write(int log_level, const char *log_context) {
    async_log_st log_st;
    log_st.log_level = log_level;
    strncpy(log_st.log_context, log_context, 1024);
    m_queue.push(log_st);
    return 0;
}
void AsyncLogWriter::close() {
    m_isFinish = true;
    m_threadPool->wait();
    delete m_threadPool;
    m_threadPool = NULL;

    map<int, int>::iterator iter;
    for (iter = m_level2fd.begin(); iter != m_level2fd.end(); ++iter) {
        ::close(iter->second); 
        iter->second = -1;
    }

}

int NetLogWriter::init(const LogConfig *log_config) {
    return 0;
}
int NetLogWriter::write(int log_level, const char *log_context) {
    return 0;
}
void NetLogWriter::close() {
}

//LogManager
LogManager::LogManager() {
    m_logConfig = NULL;
}
LogManager::~LogManager() {
    closeLogWriter();
}

int LogManager::loadConfig(const char *conf_path) {
    if (NULL == m_logConfig) {
        m_logConfig = new LogConfig();
    }
    int ret = m_logConfig->loadConfig(conf_path);
    if (0 != ret) {
        printf("load config failed\n");
        return -1;
    }
    return 0;
}
const LogConfig* getLogConfig() {
    return m_logConfig;
}
int LogManager::addLogWriter(int log_mode) {
    mapIter iter = m_logWriter.find(log_mode);
    if (iter == m_logWriter.end()) {
        m_logWriter[log_mode] = LogWriterFactory::createLogWriter(log_mode);
    }
    return m_logWriter[log_mode] == NULL ? -1 : 0;
}
int LogManager::removeLogWriter(int log_mode) {
    mapIter iter = m_logWriter.find(log_mode);
    if (iter == m_logWriter.end()) {
        return 0;
    }
    delete iter->second;
    m_logWriter.erase(log_mode);
    return 0;
}
int LogManager::initLogWriter() {
    mapIter iter = m_logWriter.begin();
    for ( ; iter != m_logWriter.end(); ++iter) {
        iter->second->init(m_logConfig);
    }
    return 0;
}
void LogManager::dispatchLog(int log_level, const char *log_context) {
    mapIter iter = m_logWriter.begin();
    for ( ; iter != m_logWriter.end(); ++iter) {
        iter->second->write(log_level, log_context);
    }
}
void LogManager::closeLogWriter() {
    mapIter iter = m_logWriter.begin();
    for ( ; iter != m_logWriter.end(); ++iter) {
        iter->second->close();
    }
}
