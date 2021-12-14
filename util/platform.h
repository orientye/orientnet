#ifndef UTIL_PLATFORM_H_
#define UTIL_PLATFORM_H_

#if defined(_WIN32)
    #include "platform/win.h"
#else
    #include "platform/unix.h"
#endif

#endif  // UTIL_PLATFORM_H_
