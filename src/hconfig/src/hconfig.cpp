#include "hconfig.h"
#include <string.h>
#include "Config.h"
#include "hlog.h"


NormalLogConfig::NormalLogConfig() :
    m_logSize(0),
    m_maxLevel(0),
    m_isOpen(false)
{
    memset(m_debugLogPath, 0, sizeof(m_debugLogPath));
    memset(m_infoLogPath, 0, sizeof(m_infoLogPath));
    memset(m_noticeLogPath, 0, sizeof(m_noticeLogPath));
    memset(m_warnLogPath, 0, sizeof(m_warnLogPath));
    memset(m_errorLogPath, 0, sizeof(m_errorLogPath));

}

int NormalLogConfig::loadConfig(const char *config_path) {
    if (NULL == config_path) {
        printf("config path is NULL\n");
        return -1;
    }
    Config config;
    if (0 != config.load(config_path)) {
        printf("config load failed, please check config file[%s]\n", config_path);
        return -1;
    }
    void *setting = NULL;
    setting = config.GetSetting("LOG_MODES");
    int len = 0;
    if (setting) {
        config.GetSettingLength(setting, len);
    }

    for (int i = 0; i < len; i++) {
        char mode[32] = {0};
        void *_setting = config.GetSetting(setting, i);
        config.GetSettingString(_setting, "MODE", mode, "");
        if (strcasecmp("Normal", mode) == 0){
            config.GetSettingValue(_setting, "IS_OPEN", m_isOpen, false);
            config.GetSettingValue(_setting, "LOG_SIZE", m_logSize, 5);
            config.GetSettingValue(_setting, "LOG_LEVEL", m_maxLevel, 5);
            config.GetSettingString(_setting, "DEBUG_LOG_PATH", m_debugLogPath, "./debug.log");
            config.GetSettingString(_setting, "INFO_LOG_PATH", m_infoLogPath, "./info.log");
            config.GetSettingString(_setting, "NOTICE_LOG_PATH", m_noticeLogPath, "./notice.log");
            config.GetSettingString(_setting, "WARN_LOG_PATH", m_warnLogPath, "./warn.log");
            config.GetSettingString(_setting, "ERROR_LOG_PATH", m_debugLogPath, "./error.log");
        }
    }

    return 0;
}


int NormalLogConfig::getLogSize() {
    return m_logSize;
}

int NormalLogConfig::getMaxLevel() {
    return m_maxLevel;
}

bool NormalLogConfig::isOpen() {
    return m_isOpen;
}


int AsyncLogConfig::loadConfig(const char *config_path) {
    if (NULL == config_path) {
        printf("config path is NULL\n");
        return -1;
    }
    Config config;
    if (0 != config.load(config_path)) {
        printf("config load failed, please check config file[%s]\n", config_path);
        return -1;
    }
    void *setting = NULL;
    setting = config.GetSetting("LOG_MODES");
    int len = 0;
    if (setting) {
        config.GetSettingLength(setting, len);
    }

    for (int i = 0; i < len; i++) {
        char mode[32] = {0};
        void *_setting = config.GetSetting(setting, i);
        config.GetSettingString(_setting, "MODE", mode, "");
        if (strcasecmp("Normal", mode) == 0){
            config.GetSettingValue(_setting, "IS_OPEN", m_isOpen, false);
            config.GetSettingValue(_setting, "LOG_SIZE", m_logSize, 5);
            config.GetSettingValue(_setting, "LOG_LEVEL", m_maxLevel, 5);
            config.GetSettingString(_setting, "DEBUG_LOG_PATH", m_debugLogPath, "./debug.log");
            config.GetSettingString(_setting, "INFO_LOG_PATH", m_infoLogPath, "./info.log");
            config.GetSettingString(_setting, "NOTICE_LOG_PATH", m_noticeLogPath, "./notice.log");
            config.GetSettingString(_setting, "WARN_LOG_PATH", m_warnLogPath, "./warn.log");
            config.GetSettingString(_setting, "ERROR_LOG_PATH", m_debugLogPath, "./error.log");
        }
    }

    return 0;
}

int AsyncLogConfig::getLogSize() {
    return m_logSize;
}

int AsyncLogConfig::getMaxLevel() {
    return m_maxLevel;
}

bool AsyncLogConfig::isOpen() {
    return m_isOpen;
}

// NetLogConfig
int NetLogConfig::loadConfig(const char *config_path) {
    if (NULL == config_path) {
        printf("config path is NULL\n");
        return -1;
    }
    Config config;
    if (0 != config.load(config_path)) {
        printf("config load failed, please check config file[%s]\n", config_path);
        return -1;
    }
    void *setting = NULL;
    setting = config.GetSetting("LOG_MODES");
    int len = 0;
    if (setting) {
        config.GetSettingLength(setting, len);
    }

    for (int i = 0; i < len; i++) {
        char mode[32] = {0};
        void *_setting = config.GetSetting(setting, i);
        config.GetSettingString(_setting, "MODE", mode, "");
        if (strcasecmp("Normal", mode) == 0){
            config.GetSettingValue(_setting, "IS_OPEN", m_isOpen, false);
            config.GetSettingValue(_setting, "LOG_SIZE", m_logSize, 5);
            config.GetSettingValue(_setting, "LOG_LEVEL", m_maxLevel, 5);
            config.GetSettingString(_setting, "IP", m_ip, "127.0.0.1");
            config.GetSettingValue(_setting, "PORT", m_port, 5555);
        }
    }



    return 0;
}
bool NetLogConfig::isOpen() {
    return m_isOpen;
}

int NetLogConfig::getLogSize() {
    return m_logSize;
}

int NetLogConfig::getMaxLevel() {
    return m_maxLevel;
}

// LogManagerInitConfig
int LogManagerInitConfig::loadConfig(const char *config_path) {
    if (NULL == config_path) {
        printf("config path is NULL\n");
        return -1;
    }
    Config config;
    if (0 != config.load(config_path)) {
        printf("config load failed, please check config file[%s]\n", config_path);
        return -1;
    }
    void *setting = NULL;
    setting = config.GetSetting("LOG_MODES");
    int len = 0;
    if (setting) {
        config.GetSettingLength(setting, len);
    }

    for (int i = 0; i < len; i++) {
        char mode[32] = {0};
        void *_setting = config.GetSetting(setting, i);
        config.GetSettingString(_setting, "MODE", mode, "");
        if (strcasecmp("Normal", mode) == 0){
            config.GetSettingValue(_setting, "IS_OPEN", m_isNormalOpen, false);
            continue;
        }
        if (strcasecmp("Async", mode) == 0){
            config.GetSettingValue(_setting, "IS_OPEN", m_isAsyncOpen, false);
            continue;
        }
        if (strcasecmp("Net", mode) == 0){
            config.GetSettingValue(_setting, "IS_OPEN", m_isNetOpen, false);
            continue;
        }
    }
    return 0;
}

bool LogManagerInitConfig::getNormalMode() {
    return m_isNormalOpen;
}

bool LogManagerInitConfig::getAsyncMode() {
    return m_isAsyncOpen;
}

bool LogManagerInitConfig::getNetMode() {
    return m_isNetOpen;
}


