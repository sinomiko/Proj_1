#pragma once

#ifdef _WIN32
#include <Winsock2.h>
#endif /* _WIN32 */

#ifdef _WIN32
typedef SOCKET fd_t;
#define __MC_INVALID_FD INVALID_SOCKET
#else
typedef int fd_t;
#define __MC_INVALID_FD -1
#endif /* _WIN32 */

//! ssize_t
#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#define __MC_LOGGING_ENABLED 1
