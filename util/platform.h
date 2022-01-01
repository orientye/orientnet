#ifndef UTIL_PLATFORM_H_
#define UTIL_PLATFORM_H_

#if defined(_WIN32)
    #include "platform/win.h"
#else
    #include "platform/unix.h"
#endif

tn::FD open_file(const char* filename, int flags, int mode);
void close_file(tn::FD fd);

#endif  // UTIL_PLATFORM_H_
