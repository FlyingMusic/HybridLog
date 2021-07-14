#include "hlog-imp.h"


int LogWriter::init(const char *log_file, int log_level, int log_size) {
    return 0;
}
int LogWriter::write(int log_level, const char *log_context) {
    return 0;
}
int LogWriter::close() {
    return 0;
}


int NormalLogWriter::init(const char *log_file, int log_level, int log_size) {
    return 0;
}
int NormalLogWriter::write(int log_level, const char *log_context) {
    return 0;
}
int NormalLogWriter::close() {
    return 0;
}

int AsyncLogWriter::init(const char *log_file, int log_level, int log_size) {
    return 0;
}
int AsyncLogWriter::write(int log_level, const char *log_context) {
    return 0;
}
int AsyncLogWriter::close() {
    return 0;
}

int NetLogWriter::init(const char *log_file, int log_level, int log_size) {
    return 0;
}
int NetLogWriter::write(int log_level, const char *log_context) {
    return 0;
}
int NetLogWriter::close() {
    return 0;
}

//LogManager
LogManager::LogManager() {

}
LogManager::~LogManager() {
    closeLogWriter();
}
int LogManager::addLogWriter(LogWriter *log_writer) {
    m_logWriter.push_back(log_writer);
    return 0;
}
int LogManager::removeLogWriter(LogWriter *log_writer) {
    m_logWriter.remove(log_writer);
    return 0;
}
int LogManager::initLogWriter(const char* log_file, int log_level, int log_size) {
    std::list<LogWriter *>::iterator iter = m_logWriter.begin();
    for ( ; iter != m_logWriter.end(); ++iter) {
        (*iter)->init(log_file, log_level, log_size);
    }
}
void LogManager::dispatchLog(int log_level, const char *log_context) {
    std::list<LogWriter *>::iterator iter = m_logWriter.begin();
    for ( ; iter != m_logWriter.end(); ++iter) {
        (*iter)->write(log_level, log_context);
    }
}
int LogManager::closeLogWriter() {
    std::list<LogWriter *>::iterator iter = m_logWriter.begin();
    for ( ; iter != m_logWriter.end(); ++iter) {
        (*iter)->close();
    }
}
#endif
