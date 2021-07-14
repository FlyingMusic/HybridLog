#include "hlog-imp.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "utility.h"
#include "hlog-factory.h"


using namespace std;

int LogWriter::init(const char *log_file, int log_level, int log_size) {
    return 0;
}
int LogWriter::write(int log_level, const char *log_context) {
    return 0;
}
void LogWriter::close() {
}


int NormalLogWriter::init(const char *log_file, int log_level, int log_size) {
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

int AsyncLogWriter::init(const char *log_file, int log_level, int log_size) {
    return 0;
}
int AsyncLogWriter::write(int log_level, const char *log_context) {
    return 0;
}
void AsyncLogWriter::close() {
}

int NetLogWriter::init(const char *log_file, int log_level, int log_size) {
    return 0;
}
int NetLogWriter::write(int log_level, const char *log_context) {
    return 0;
}
void NetLogWriter::close() {
}

//LogManager
LogManager::LogManager() {

}
LogManager::~LogManager() {
    closeLogWriter();
}
int LogManager::addLogWriter(int log_mode) {
    mapIter iter = m_logWriter.find(log_mode);
    if (iter == m_logWriter.end()) {
        m_logWriter[log_mode] = LogWriterFactory::createLogWriter(log_mode);
    }
    return 0;
}
int LogManager::removeLogWriter(int log_mode) {
    m_logWriter.erase(log_mode);
    return 0;
}
int LogManager::initLogWriter(const char* log_file, int log_level, int log_size) {
    mapIter iter = m_logWriter.begin();
    for ( ; iter != m_logWriter.end(); ++iter) {
        iter->second->init(log_file, log_level, log_size);
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
