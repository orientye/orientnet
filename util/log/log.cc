#include "util/log/log.h"

Logger::Logger() {}

Logger::~Logger() {}

Logger& Logger::get_logger() {
  static Logger logger;
  return logger;
}

void Logger::log(LogLevel lvl, const char* s) {}

void Logger::set_level(LogLevel level) {}
void Logger::set_file(const char* filename) {}
