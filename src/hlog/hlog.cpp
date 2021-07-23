#include "hlog.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <sys/time.h>
#include "hlog-imp.h"
#include "hconfig-factory.h"

static LogManager *g_logMgr = NULL;
const char *g_level_name[] = {"NO-SET", "DEBUG", "INFO", "NOTICE", "WARN", "ERROR"};

int hlog_init(const char *conf_file) {
    if (NULL == conf_file) {
        printf("hlog init param is NULL\n");
        return -1;
    }
    if (NULL == g_logMgr) {
        g_logMgr = new LogManager(); 
    }
    int ret = g_logMgr->init(conf_file);
    if (0 != ret) {
        printf("log manager load config failed\n");
        return -1;
    }
    LogManagerInitConfig* log_config = (LogManagerInitConfig*)ConfigFactory::getConfig(LOG_MANAGER_INIT);
    if (NULL == log_config) {
        printf("log config in log manager is NULL\n");
        return -1;
    }
    ret = log_config->loadConfig(conf_file);
    if (0 != ret) {
        printf("load config failed in hlog_init\n");
        return -1;
    }
    if (log_config->getNormalMode()) {
        ret = g_logMgr->addLogWriter(NORMAL_MODE);
        if (0 != ret) {
            printf("add normal logwriter failed\n");
        }
    }
    if (log_config->getAsyncMode()) {
        ret = g_logMgr->addLogWriter(ASYNC_MODE);
        if (0 != ret) {
            printf("add async logwriter failed\n");
        }
    }
    if (log_config->getNetMode()) {
        ret = g_logMgr->addLogWriter(NET_MODE);
        if (0 != ret) {
            printf("add net logwriter failed\n");
        }
    }
    delete log_config;
    ret = g_logMgr->initLogWriter();
    if (0 != ret) {
        printf("init log writer failed!\n");
    }
    return 0;
}

static void log_format(int level, const char *prefix, const char *func, const char *fmt, va_list ap) {
    char new_format[1024] = {0};
    char buffer[1024] = {0};
    if (prefix) {
        snprintf(new_format, 1024, "%s", prefix);
        //strcpy(new_format, prefix);
    }
    if (func) {
        snprintf(new_format + strlen(new_format), 1024 - strlen(new_format), "[%s] ", func);
      //  strcpy(new_format + strlen(new_format), func);
    }

    char formatted[100] = {0};
    struct timeval nowtime;
    gettimeofday(&nowtime, NULL);
    time_t t = nowtime.tv_sec;
    struct tm currentTime;
    localtime_r(&t, &currentTime);
    strftime(formatted, sizeof(formatted), "%Y-%m-%d %H:%M:%S", &currentTime);
    if(new_format[0] != 0){
        snprintf(buffer, 1024, "%s,%03ld [%s] %s %s\n", formatted, nowtime.tv_usec/1000, g_level_name[level], new_format, fmt);
        //strcpy(buffer, "hllll");
    }else{
        snprintf(buffer, 1024, "%s,%03ld [%s] %s\n", formatted, nowtime.tv_usec/1000, g_level_name[level], fmt);
       // strcpy(buffer, "hllll");
    }
    vsnprintf(new_format, 1024, buffer, ap);
   // strcpy(new_format, "hello hello\n");
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

void log_decoder_vvv(int level, const char *prefix, const char *func, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    log_format(level, prefix, func, fmt, ap);
    va_end(ap);
    return;
}

void hlog_close() {
    if (g_logMgr) {
        delete g_logMgr;
        g_logMgr = NULL;
    }
}

