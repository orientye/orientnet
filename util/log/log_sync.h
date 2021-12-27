#ifndef UTIL_LOG_LOG_SYNC_H_
#define UTIL_LOG_LOG_SYNC_H_

#include "util/platform.h"

class SyncLogger {
 protected:
  SyncLogger(const char* file_name);
  ~SyncLogger();

  SyncLogger(const SyncLogger&) = delete;
  SyncLogger& operator=(const SyncLogger&) = delete;
  SyncLogger(SyncLogger&&) = delete;
  SyncLogger& operator=(SyncLogger&&) = delete;

 public:
  void critical(const char* s);

  void set_file(const char* filename);

 private:
  tn::FD fd_;
};

#endif  // UTIL_LOG_LOG_SYNC_H_
