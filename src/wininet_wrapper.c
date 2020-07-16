#include <windows.h>
#include <wininet.h>

#include "config.h"

extern proxy_config_t gconfig;

BOOL WINAPI _InternetGetConnectedState(
    LPDWORD lpdwFlags,
    DWORD   dwReserved
)
{
    #ifdef DEBUG
    $("InternetGetConnectedState");
    #endif

    if (gconfig.use_proxy) {
        *lpdwFlags = INTERNET_CONNECTION_PROXY;
        return TRUE;
    } else {
        return InternetGetConnectedState(lpdwFlags, dwReserved);
    }
}
