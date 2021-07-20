#ifndef _HYBRID_LOG_INC_
#define _HYBRID_LOG_INC_

typedef enum HLOG_LEVEL {
    LEVEL_NOTSET = 0x00,
    LEVEL_DEBUG,
    LEVEL_INFO,
    LEVEL_NOTICE,
    LEVEL_WARN,
    LEVEL_ERROR,
    LEVEL_MAX
} DLOG_LEVEL;

void log_decoder_v(int level, const char *fmt, ...);
void log_decoder_vv(int level, const char *prefix, const char *func, const char *fmt, ...);

#define LOGI(fmt,...) log_decoder_v(LEVEL_INFO,fmt,##__VA_ARGS__)
#define LOGD(fmt,...) log_decoder_v(LEVEL_DEBUG,fmt,##__VA_ARGS__)

#define LOG_DEBUG(fmt,...)   log_decoder_v(LEVEL_DEBUG,fmt,##__VA_ARGS__)
#define LOG_WARN(fmt,...)    log_decoder_v(LEVEL_WARN,fmt,##__VA_ARGS__)
#define LOG_ERROR(fmt,...)   log_decoder_v(LEVEL_ERROR,fmt,##__VA_ARGS__)
#define LOG_INFO(fmt,...)    log_decoder_v(LEVEL_INFO,fmt,##__VA_ARGS__)
#define LOG_NOTICE(fmt,...)  log_decoder_v(LEVEL_NOTICE,fmt,##__VA_ARGS__)

#define LOG_D(prefix,fmt,...) log_decoder_vv(LEVEL_DEBUG,prefix,__FUNCTION__,fmt,##__VA_ARGS__)
#define LOG_W(prefix,fmt,...) log_decoder_vv(LEVEL_WARN,prefix,__FUNCTION__,fmt,##__VA_ARGS__)
#define LOG_E(prefix,fmt,...) log_decoder_vv(LEVEL_ERROR,prefix,__FUNCTION__,fmt,##__VA_ARGS__)
#define LOG_I(prefix,fmt,...) log_decoder_vv(LEVEL_INFO,prefix,__FUNCTION__,fmt,##__VA_ARGS__)
#define LOG_N(prefix,fmt,...) log_decoder_vv(LEVEL_NOTICE,prefix,__FUNCTION__,fmt,##__VA_ARGS__)

int hlog_init(const char* conf_file);

void hlog_close();

#endif
