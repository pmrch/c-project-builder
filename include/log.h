#ifndef LOG_H
#define LOG_H

// Log levels
#define LOG_LEVEL_DEBUG 0
#define LOG_LEVEL_INFO 1
#define LOG_LEVEL_WARN 2
#define LOG_LEVEL_ERROR 3

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_INFO
#endif

#if defined(__GNUC__) && !defined(_WIN32)
    #define PRINTF_LIKE(fmt_idx, arg_idx) __attribute__((format(printf, 6, 7)))
#else
    #define PRINTF_LIKE(fmt_idx, arg_idx)
#endif

#include <stdio.h>
#include <stdarg.h>

// Forward declaration of the internal worker function
inline void log_internal(const char* level_str, const char* color, const char* file, int line, const char* func, const char* fmt, ...) 
PRINTF_LIKE(6, 7) {
    fprintf(stderr, "%s[%s]\x1b[0m %s:%d:%s: ", color, level_str, file, line, func);
    
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    
    fprintf(stderr, "\n");    
};

#if LOG_LEVEL <= LOG_LEVEL_DEBUG
#define LOG_DEBUG(fmt, ...) log_internal("DEBUG", "\x1b[36m", __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#else
#define LOG_DEBUG(fmt, ...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_INFO
#define LOG_INFO(fmt, ...)  log_internal("INFO",  "\x1b[32m", __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#else
#define LOG_INFO(fmt, ...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_WARN
#define LOG_WARN(fmt, ...)  log_internal("WARN",  "\x1b[33m", __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#else
#define LOG_WARN(fmt, ...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_ERROR
#define LOG_ERROR(fmt, ...) log_internal("ERROR", "\x1b[31m", __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#else
#define LOG_ERROR(fmt, ...)
#endif

#endif