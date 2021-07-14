#include "hlog.h"

static LogManager *g_logMgr = NULL;

int set_log_level_file(const char* log_file, int log_level, int log_size, bool singleLevel, int log_mode) {
    if (NULL == g_logMgr) {
        g_logMgr = new LogManager(); 
    }

    int ret = 0;
    if (log_mode & NORMAL_MODE) {
        ret |= g_logMgr->addLogWriter(LogWriterFactory::createLogWriter(NORMAL_LOG));
    } else if (log_mode & ASYNC_MODE) {
        ret |= g_logMgr->addLogWriter(LogWriterFactory::createLogWriter(ASYNC_LOG));
    } else if (log_mode & NET_MODE) {
        ret |= g_logMgr->addLogWriter(LogWriterFactory::createLogWriter(NET_LOG));
    }
    
    if (0 != ret) {
        printf("add log Writer failed!\n");
        return ret;
    }
    ret = g_logMgr->initLogWriter(log_file, log_level, log_size);
    if (0 != ret) {
        printf("init log Writer failed!\n");
        return ret;
    }

    return ret;
}

static void log_format(int level, const char *prefix, const char *func, const char *fmt, va_list ap) {
    if(g_threadLog){
        if(!g_threadLog->isLogLevel(level))
            return;
    }
    char new_format[1024] = {0};
    char buffer[1024] = {0};
    if (prefix) {
        snprintf(new_format, 1024, "%s", prefix);
    }
    if (func) {
        snprintf(new_format + strlen(new_format), 1024 - strlen(new_format), "[%s] ", func);
    }

    char formatted[100] = {0};
    struct timeval nowtime;
    gettimeofday(&nowtime, NULL);
    time_t t = nowtime.tv_sec;
    struct tm currentTime;
    localtime_r(&t, &currentTime);
    strftime(formatted, sizeof(formatted), "%Y-%m-%d %H:%M:%S", &currentTime);
    if(new_format[0] != 0){
        snprintf(buffer, 1024, "%s,%03ld [%s] %s %s", formatted, nowtime.tv_usec/1000, g_level_name[level], new_format, fmt);
    }else{
        snprintf(buffer, 1024, "%s,%03ld [%s] %s", formatted, nowtime.tv_usec/1000, g_level_name[level], fmt);
    }
    vsnprintf(new_format, 1024, buffer, ap);
    g_logMgr->dispatchLog(level, new_format);
    return;
}

void log_decoder_v(int level,const char *fmt,...) {
    va_list ap;
    va_start(ap,fmt);
    log_format(level, NULL, NULL, fmt, ap);
    va_end(ap);
    return;
}

void log_decoder_vv(int level,const char *prefix,const char *func,const char *fmt,...) {
    va_list ap;
    va_start(ap,fmt);
    log_format(level, prefix, func, fmt, ap);
    va_end(ap);
    return;
}

void log_decoder_vvv(int level, const char *prefix, const char *func, const char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    log_format(level, prefix, func, fmt, ap);
    va_end(ap);
    return;
}

void close_log(){
    if (g_logMgr) {
        delete g_logMgr;
        g_logMgr = NULL;
    }
}

