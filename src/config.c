#include <windows.h>
#include "config.h"

void read_proxy_config(proxy_config_t* config)
{
    static LPCWSTR INI_FILE_NAME = L".\\geproxy.ini";

    static LPCWSTR PROXY_SECTION_NAME = L"Proxy";
    static LPCWSTR PROXY_USE_KEY = L"Use";
    static LPCWSTR PROXY_ADDRESS_KEY = L"Address";

    static LPCWSTR DEFAULT_PROXY_ADDRESS = L"127.0.0.1:8081";

    config->use_proxy = GetPrivateProfileIntW(
        PROXY_SECTION_NAME, PROXY_USE_KEY, true, INI_FILE_NAME
    );

    if (config->use_proxy) {

        DWORD nSize = sizeof(config->address) / sizeof(config->address[0]);

        config->address_len = GetPrivateProfileStringW(
            PROXY_SECTION_NAME, PROXY_ADDRESS_KEY, DEFAULT_PROXY_ADDRESS,
            config->address, nSize-1, INI_FILE_NAME
        );

        if (config->address_len == 0) {
            config->use_proxy = false;
        } else {
            config->address_len++; // include NULL character
        }
    }
}
