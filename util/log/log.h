#ifndef UTIL_LOG_LOG_H_
#define UTIL_LOG_LOG_H_

#include <cstdint>

#include "util/platform.h"

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
