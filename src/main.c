#include <windows.h>

#include "config.h"

proxy_config_t gconfig = {
    .initialized = false,
    .use_proxy   = false,
    .address     = {0},
    .address_len = 0,
};

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hinstDLL);
        if (!gconfig.initialized) {
            gconfig.initialized = true;
            read_proxy_config(&gconfig);
            #ifdef DEBUG
            $("Initialized");
            #endif
        }
        break;

    case DLL_PROCESS_DETACH:
        #ifdef DEBUG
        $("Process detach");
        #endif
        break;
    }
    return TRUE;
}
