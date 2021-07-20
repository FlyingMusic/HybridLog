#ifndef __LOG_CONFIG__
#define __LOG_CONFIG__

#include "Config.h"

class LogConfig {
public:
    LogConfig();
    ~LogConfig();
    int loadConfig(const char *config_path);
    int getLogSize();
    int getMaxLevel();
    bool getNormalMode();
    bool getAsyncMode();
    bool getNetMode();
    const char *getDebugLogPath();
    const char *getInfoLogPath();
    const char *getNoticeLogPath();
    const char *getWarnLogPath();
    const char *getErrorLogPath();
private:
    bool m_isNormalModeOn;
    bool m_isAsyncModeOn;
    bool m_isNetModeOn;
    int m_logSize;
    int m_maxLevel;
    char m_debugLogPath[1024];
    char m_infoLogPath[1024];
    char m_noticeLogPath[1024];
    char m_warnLogPath[1024];
    char m_errorLogPath[1024];
};

#endif
