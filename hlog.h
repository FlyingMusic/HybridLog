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

#define NORMAL_MODE (0x1 << 0)
#define ASYNC_MODE  (0x1 << 1)
#define NET_MODE    (0x1 << 2)

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

/**
 * Set log level and the corresponding file.
 *
 * Set where to record logs for a specific level, if not called, all logs would
 * be directed to the file called "access.log" of current directory, otherwise
 * logs higher than log_level would be directed to log_file. Logs with lower
 * priority would be appended to more files.
 *
 * @param: log_file: where to record logs
 * @param: log_level: log level
 * @param: log_size: maximum size of log file in unit of MB, positive number
 * means file size limit, non-positive number means no limit of log size,
 * default limit is 10MB
 * @param: singleLevel: Whether it is a singleLevel mode, if false, every log level
 * correspond to a log instance, namely one level only output one file. */
int set_log_level_file(const char* log_file, int log_level, int log_size = 10, 
        bool singleLevel = true, int log_mode = NORMAL_MODE);


/**
 * Set the switch allowed roll over or not duing log writing.
 *
 * @param : allow
 *          False means : Not roll over log during writing
 *          True means : roll over will be executed when the log size reaches the set maximum value
 * */
void set_log_allow_roll_over(bool allow);

/**
 * roll over will be executed when the log size reaches the set maximum value.
 * */
void execute_log_roll_over();

void close_log();
#endif
