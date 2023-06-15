#ifndef UTIL_LOG_LOG_H_
#define UTIL_LOG_LOG_H_

#include <cstdint>

#include "util/platform.h"

#define __log(level, ...)                             \
  do {                                                \
    if (level <= Logger::getLogger().getLogLevel()) { \
      Logger::getLogger().log(level, __VA_ARGS__);    \
    }                                                 \
  } while (0)
#endif

#define LOG_TRACE(...) __log(Logger::kTRACE, __VA_ARGS__)
#define LOG_DEBUG(...) __log(Logger::kDEBUG, __VA_ARGS__)
#define LOG_INFO(...) __log(Logger::kINFO, __VA_ARGS__)
#define LOG_WARN(...) __log(Logger::kWARN, __VA_ARGS__)
#define LOG_ERROR(...) __log(Logger::kERROR, __VA_ARGS__)
#define LOG_FATAL(...) __log(Logger::kFATAL, __VA_ARGS__)

class Logger {
  enum class LogLevel : std::int8_t {
    kTrace = 0,
    kDebug,
    kInfo,
    kWarn,
    kError,
    kFatal
  };

 protected:
  Logger();
  ~Logger();

  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;
  Logger(Logger&&) = delete;
  Logger& operator=(Logger&&) = delete;

 public:
  static Logger& get_logger();

  void log(LogLevel lvl, const char* s);

  void set_level(LogLevel level);
  void set_file(const char* filename);

 private:
  LogLevel level_;
  tn::FD fd_;
};

#endif  // UTIL_LOG_LOG_H_
