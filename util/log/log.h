#ifndef UTIL_LOG_LOG_H_
#define UTIL_LOG_LOG_H_

#include <cstdint>

class Logger {
  enum class LogLevel : std::int8_t {
    kTrace = 0,
    kDebug,
    kInfo,
    kWarn,
    kError,
    kFatal
  };

 public:
  void trace(const char* s);
  void debug(const char* s);
  void info(const char* s);
  void warn(const char* s);
  void error(const char* s);
  void fatal(const char* s);

  void set_config_file(const char* cf_name);

  void set_flush_mode(bool sync);
  void set_level(LogLevel level);
  void set_file(const char* file_name);
};

#endif  // UTIL_LOG_LOG_H_
