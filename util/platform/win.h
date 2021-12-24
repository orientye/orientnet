#ifndef UTIL_PLATFORM_WIN_H_
#define UTIL_PLATFORM_WIN_H_

#include <windows.h>

namespace tn {
    using os_socket = SOCKET;
    using os_fd = HANDLE;
};

#endif  // UTIL_PLATFORM_WIN_H_
