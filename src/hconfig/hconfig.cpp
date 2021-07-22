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
#if 0
    void *setting = NULL;
    setting = config.GetSetting("MODELS");
    int len = 0;
    if (setting) {
        config.GetSettingLength(setting, len);
    }

    snprintf(base_res_path, MAX_RES_PATH_LEN, "%s/cmn", config->GetFilepath());
    for (int i = 0; i < len; i++) {
        char lang[32] = {0};
        void *_setting = config->GetSetting(setting, i);
        config->GetSettingString(_setting, "LANG", lang, "");
        if(strcasecmp(m_lang, lang) == 0){
            config->GetSettingString(_setting, "DIRECTORY", base_res_path, "");
            break;
        }
    }
    config.GetValue("LOG_SIZE", m_logSize, 10);
    config.GetValue("LOG_LEVEL", m_maxLevel, LEVEL_MAX);
    config.GetValue("NORMAL_MODE", m_isNormalModeOn, false);
    config.GetValue("ASYNC_MODE", m_isAsyncModeOn, false);
    config.GetValue("NET_MODE", m_isNetModeOn, false);
    config.GetString("DEBUG_LOG_PATH", m_debugLogPath, "./debug.log");
    config.GetString("INFO_LOG_PATH", m_infoLogPath, "./info.log");
    config.GetString("NOTICE_LOG_PATH", m_noticeLogPath, "./notice.log");
    config.GetString("WARN_LOG_PATH", m_warnLogPath, "./warn.log");
    config.GetString("ERROR_LOG_PATH", m_errorLogPath, "./error.log");
#endif
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








int LogManagerInitConfig::loadConfig(const char *config_path) {
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


