#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <windows.h>
#include <stdbool.h>

#ifdef DEBUG
#define $(x) ( OutputDebugStringA("geproxy: " x) )
#endif

typedef struct {
    bool     initialized;
    bool     use_proxy;
    wchar_t  address[255];
    size_t   address_len; // including NULL character
} proxy_config_t;

void read_proxy_config(proxy_config_t * config);

#endif // CONFIG_H_INCLUDED
