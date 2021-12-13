#include "util/log/log.h"

void Logger::trace(const char *s) {}
void Logger::debug(const char *s) {}
void Logger::info(const char *s) {}
void Logger::warn(const char *s) {}
void Logger::error(const char *s) {}
void Logger::fatal(const char *s) {}

void Logger::setLogLevel(LogLevel level) {}
void Logger::setLogFile(const char *file_name) {}