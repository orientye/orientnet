#include "util/log/log.h"

void Logger::trace(const char* s) {}
void Logger::debug(const char* s) {}
void Logger::info(const char* s) {}
void Logger::warn(const char* s) {}
void Logger::error(const char* s) {}
void Logger::fatal(const char* s) {}

void Logger::set_config_file(const char* cf_name) {}

void Logger::set_flush_mode(bool sync) {}
void Logger::set_level(LogLevel level) {}
void Logger::set_file(const char* file_name) {}
