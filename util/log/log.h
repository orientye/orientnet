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

 protected:
  Logger();
  ~Logger();

  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;
  Logger(Logger&&) = delete;
  Logger& operator=(Logger&&) = delete;

 public:
  static Logger& get_logger();

  void trace(const char* s);
  void debug(const char* s);
  void info(const char* s);
  void warn(const char* s);
  void error(const char* s);
  void fatal(const char* s);

  void set_config_file(const char* cf_name);

  void set_level(LogLevel level);
  void set_file(const char* file_name);

 private:
  LogLevel level_;
};

#endif  // UTIL_LOG_LOG_H_
