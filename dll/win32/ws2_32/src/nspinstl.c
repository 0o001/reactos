/*
 * COPYRIGHT:   See COPYING in the top level directory
 * PROJECT:     ReactOS WinSock 2 API
 * FILE:        dll/win32/ws2_32/src/nspinstl.c
 * PURPOSE:     Namespace Provider Installation
 * PROGRAMMER:  Alex Ionescu (alex@relsoft.net)
 */

/* INCLUDES ******************************************************************/

#include <ws2_32.h>

#define NDEBUG
#include <debug.h>

/* FUNCTIONS *****************************************************************/

/*
 * @unimplemented
 */
INT
WSPAPI
WSCEnableNSProvider(IN LPGUID lpProviderId,
                    IN BOOL fEnable)
{
    UNIMPLEMENTED;
    SetLastError(WSAEINVAL);
    return SOCKET_ERROR;
}

#ifdef _WIN64
/*
 * @unimplemented
 */
INT
WSPAPI
WSCEnableNSProvider32(
    _In_ LPGUID lpProviderId,
    _In_ BOOL fEnable)
{
    UNIMPLEMENTED;
    SetLastError(WSAEINVAL);
    return SOCKET_ERROR;
}
#endif

/*
 * @unimplemented
 */
INT
WSPAPI
WSCInstallNameSpace(IN LPWSTR lpszIdentifier,
                    IN LPWSTR lpszPathName,
                    IN DWORD dwNameSpace,
                    IN DWORD dwVersion,
                    IN LPGUID lpProviderId)
{
    UNIMPLEMENTED;
    SetLastError(WSAEINVAL);
    return SOCKET_ERROR;
}

#ifdef _WIN64
/*
 * @unimplemented
 */
INT
WSPAPI
WSCInstallNameSpace32(
    _In_ LPWSTR lpszIdentifier,
    _In_ LPWSTR lpszPathName,
    _In_ DWORD dwNameSpace,
    _In_ DWORD dwVersion,
    _In_ LPGUID lpProviderId)
{
    UNIMPLEMENTED;
    SetLastError(WSAEINVAL);
    return SOCKET_ERROR;
}
#endif

/*
 * @unimplemented
 */
INT
WSPAPI
WSCUnInstallNameSpace(IN LPGUID lpProviderId)
{
    UNIMPLEMENTED;
    SetLastError(WSAEINVAL);
    return SOCKET_ERROR;
}

#ifdef _WIN64
/*
 * @unimplemented
 */
INT
WSPAPI
WSCUnInstallNameSpace32(
    _In_ LPGUID lpProviderId)
{
    UNIMPLEMENTED;
    SetLastError(WSAEINVAL);
    return SOCKET_ERROR;
}
#endif

/*
 * @unimplemented
 */
INT
WSPAPI
WSCUpdateProvider(LPGUID lpProviderId,
                  const WCHAR FAR * lpszProviderDllPath,
                  const LPWSAPROTOCOL_INFOW lpProtocolInfoList,
                  DWORD dwNumberOfEntries,
                  LPINT lpErrno)
{
    UNIMPLEMENTED;
    SetLastError(WSAEINVAL);
    return SOCKET_ERROR;
}

#ifdef _WIN64
/*
 * @unimplemented
 */
int
WSPAPI
WSCUpdateProvider32(
    _In_ LPGUID lpProviderId,
    _In_z_ const WCHAR FAR* lpszProviderDllPath,
    _In_reads_(dwNumberOfEntries) const LPWSAPROTOCOL_INFOW lpProtocolInfoList,
    _In_ DWORD dwNumberOfEntries,
    _Out_ LPINT lpErrno)
{
    UNIMPLEMENTED;
    SetLastError(WSAEINVAL);
    return SOCKET_ERROR;
}
#endif

/*
 * @unimplemented
 */
INT
WSPAPI
WSCWriteNameSpaceOrder(LPGUID lpProviderId,
                       DWORD dwNumberOfEntries)
{
    UNIMPLEMENTED;
    SetLastError(WSAEINVAL);
    return SOCKET_ERROR;
}

#ifdef _WIN64
/*
 * @unimplemented
 */
int
WSPAPI
WSCWriteNameSpaceOrder32(
    IN LPGUID lpProviderId,
    IN DWORD dwNumberOfEntries)
{
    UNIMPLEMENTED;
    SetLastError(WSAEINVAL);
    return SOCKET_ERROR;
}
#endif

#ifdef _WIN64
/*
 * @unimplemented
 */
INT
WSAAPI
WSCEnumNameSpaceProviders32(
    _Inout_ LPDWORD lpdwBufferLength,
    _Out_writes_bytes_(*lpdwBufferLength) LPWSANAMESPACE_INFOW lpnspBuffer)
{
    UNIMPLEMENTED;
    SetLastError(WSAEINVAL);
    return SOCKET_ERROR;
}
#endif
