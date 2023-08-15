/*
 * COPYRIGHT:   See COPYING in the top level directory
 * PROJECT:     ReactOS WinSock 2 API
 * FILE:        dll/win32/ws2_32/src/spinstal.c
 * PURPOSE:     Transport Service Provider Installation
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
WSCInstallProvider(IN LPGUID lpProviderId,
                   IN CONST WCHAR * lpszProviderDllPath,
                   IN CONST LPWSAPROTOCOL_INFOW lpProtocolInfoList,
                   IN DWORD dwNumberOfEntries,
                   OUT LPINT lpErrno)
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
WSCInstallProvider64_32(
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
WSCDeinstallProvider(IN LPGUID lpProviderId,
                     OUT LPINT lpErrno)
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
WSCDeinstallProvider32(
    _In_ LPGUID lpProviderId,
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
WSCWriteProviderOrder(IN LPDWORD lpwdCatalogEntryId,
                      IN DWORD dwNumberOfEntries)
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
WSCWriteProviderOrder32(
    IN LPDWORD lpwdCatalogEntryId,
    IN DWORD dwNumberOfEntries)
{
    UNIMPLEMENTED;
    SetLastError(WSAEINVAL);
    return SOCKET_ERROR;
}
#endif
