#include <string.h>
#include <windows.h>
#include <winhttp.h>

#include "config.h"

extern proxy_config_t gconfig;

static LPWSTR alloc_proxy_str(void)
{
    LPWSTR str = NULL;

    size_t sz = gconfig.address_len * sizeof(wchar_t);
    HGLOBAL ptr = GlobalAlloc(GMEM_FIXED, sz);

    if (ptr != NULL) {
        str = memcpy(ptr, gconfig.address, sz);
    }
    return str;
}

BOOL WINAPI _WinHttpGetIEProxyConfigForCurrentUser(
	WINHTTP_CURRENT_USER_IE_PROXY_CONFIG *pProxyConf
)
{
	#ifdef DEBUG
	$("WinHttpGetIEProxyConfigForCurrentUser");
    #endif

	if (gconfig.use_proxy) {
		pProxyConf->fAutoDetect = FALSE;
		pProxyConf->lpszAutoConfigUrl = NULL;
		pProxyConf->lpszProxy = alloc_proxy_str();
		pProxyConf->lpszProxyBypass = WINHTTP_NO_PROXY_BYPASS;
		return TRUE;
	} else {
		return WinHttpGetIEProxyConfigForCurrentUser(pProxyConf);
	}
}

HINTERNET WINAPI _WinHttpOpen(
	LPCWSTR pwszUserAgent,
	DWORD   dwAccessType,
	LPCWSTR pwszProxyName,
	LPCWSTR pwszProxyBypass,
	DWORD   dwFlags
)
{
	#ifdef DEBUG
	$("WinHttpOpen");
	#endif
	return WinHttpOpen(pwszUserAgent, dwAccessType, pwszProxyName, pwszProxyBypass, dwFlags);
}

BOOL WINAPI _WinHttpCloseHandle(HINTERNET hInternet)
{
	#ifdef DEBUG
	$("WinHttpCloseHandle");
	#endif
	return WinHttpCloseHandle(hInternet);
}

BOOL WINAPI _WinHttpGetProxyForUrl(
	HINTERNET hSession,
	LPCWSTR lpcwszUrl,
	WINHTTP_AUTOPROXY_OPTIONS *pAutoProxyOptions,
	WINHTTP_PROXY_INFO *pProxyInfo
)
{
	#ifdef DEBUG
	$("WinHttpGetProxyForUrl");
	#endif
	return WinHttpGetProxyForUrl(hSession, lpcwszUrl, pAutoProxyOptions, pProxyInfo);
}

BOOL WINAPI _WinHttpGetDefaultProxyConfiguration(WINHTTP_PROXY_INFO *pProxyInfo)
{
	#ifdef DEBUG
	$("WinHttpGetDefaultProxyConfiguration");
    #endif
	return WinHttpGetDefaultProxyConfiguration(pProxyInfo);
}

BOOL WINAPI _WinHttpDetectAutoProxyConfigUrl(
	DWORD  dwAutoDetectFlags,
	LPWSTR *ppwszAutoConfigUrl
)
{
	#ifdef DEBUG
	$("WinHttpDetectAutoProxyConfigUrl");
	#endif
	return WinHttpDetectAutoProxyConfigUrl(dwAutoDetectFlags, ppwszAutoConfigUrl);
}
