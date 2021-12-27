#ifndef UTIL_PLATFORM_WIN_H_
#define UTIL_PLATFORM_WIN_H_

#include <windows.h>

namespace tn {
    using Socket = SOCKET;
    using FD = HANDLE;
};

#endif  // UTIL_PLATFORM_WIN_H_
