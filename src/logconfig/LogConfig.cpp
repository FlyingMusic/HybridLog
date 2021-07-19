#include "LogConfig.h"
#include <string.h>
#include "Config.h"
#include "hlog.h"


LogConfig::LogConfig() : 
    m_logSize(0),
    m_maxLevel(0) 
{
    memset(m_debugLogPath, 0, sizeof(m_debugLogPath));
    memset(m_infoLogPath, 0, sizeof(m_infoLogPath));
    memset(m_noticeLogPath, 0, sizeof(m_noticeLogPath));
    memset(m_warnLogPath, 0, sizeof(m_warnLogPath));
    memset(m_errorLogPath, 0, sizeof(m_errorLogPath));
}

LogConfig::~LogConfig() {

}

int LogConfig::loadConfig(const char *config_path) {
    if (NULL == config_path) {
        printf("config path is NULL\n");
        return -1;
    }
    Config config;
    if (0 != config.load(config_path)) {
        printf("config load failed, please check config file[%s]\n", config_path);
        return -1;
    }
    config.GetValue("LOG_SIZE", m_logSize, 10);
    config.GetValue("LOG_LEVEL", m_maxLevel, LEVEL_MAX);
    config.GetString("DEBUG_LOG_PATH", m_debugLogPath, "./debug.log");
    config.GetString("INFO_LOG_PATH", m_infoLogPath, "./info.log");
    config.GetString("NOTICE_LOG_PATH", m_noticeLogPath, "./notice.log");
    config.GetString("WARN_LOG_PATH", m_warnLogPath, "./warn.log");
    config.GetString("ERROR_LOG_PATH", m_errorLogPath, "./error.log");
    return 0;
}

int LogConfig::getLogSize() {
    return m_logSize;
}

int LogConfig::getMaxLevel() {
    return m_maxLevel;
}

const char* LogConfig::getDebugLogPath() {
    return m_debugLogPath;
}

const char* LogConfig::getInfoLogPath() {
    return m_infoLogPath;
}

const char* LogConfig::getNoticeLogPath() {
    return m_noticeLogPath;
}

const char* LogConfig::getWarnLogPath() {
    return m_warnLogPath;
}

const char* LogConfig::getErrorLogPath() {
    return m_errorLogPath;
}
