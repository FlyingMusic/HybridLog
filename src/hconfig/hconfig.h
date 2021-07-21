#ifndef __HCONFIG__
#define __HCONFIG__

#include "Config.h"

typedef enum {
    NORMAL_LOG_MANAGER = 0x0,
    ASYNC_LOG_MANAGER,
    NET_LOG_MANAGER,
} ConfigMode;

class HybridConfig {
    HybridConfig(){ }
    virtual ~HybridConfig() { }
};

class NormalLogConfig : public HybridConfig {
public:
    NormalLogConfig();
    int loadConfig(const char *config_path);
    int getLogSize();
    int getMaxLevel();
    bool isOpen();
private:
    char m_debugLogPath[1024];
    char m_infoLogPath[1024];
    char m_noticeLogPath[1024];
    char m_warnLogPath[1024];
    char m_errorLogPath[1024];
    int m_logSize;
    int m_maxLevel;
    bool m_isOpen;
}

class AsyncLogConfig : public HybridConfig {
public:
    int loadConfig(const char *config_path);
    int getLogSize();
    int getMaxLevel();
    bool isOpen();
private:
    char m_debugLogPath[1024];
    char m_infoLogPath[1024];
    char m_noticeLogPath[1024];
    char m_warnLogPath[1024];
    char m_errorLogPath[1024];
    int m_logSize;
    int m_maxLevel;
    bool m_isOpen;
}

class NetLogConfig : public HybridConfig {
public:
    int loadConfig(const char *config_path);
    int getLogSize();
    int getMaxLevel();
    bool isOpen();
private:
    char m_serverIp[1024];
    char m_serverPort[1024];
    int m_logSize;
    int m_maxLevel;
    bool m_isOpen;
}

#endif
