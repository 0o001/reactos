
#include "k32_vista.h"

#include <ndk/exfuncs.h>
#include <wine/config.h>
#include <wine/port.h>

DWORD WINAPI RtlRunOnceExecuteOnce( RTL_RUN_ONCE *once, PRTL_RUN_ONCE_INIT_FN func,
                                           void *param, void **context );

_IRQL_requires_max_(APC_LEVEL)
_Must_inspect_result_
NTSYSAPI
NTSTATUS
NTAPI
RtlRunOnceBeginInitialize(
    _Inout_ PRTL_RUN_ONCE RunOnce,
    _In_ ULONG Flags,
    _Outptr_opt_result_maybenull_ PVOID * Context);

_IRQL_requires_max_(APC_LEVEL)
NTSYSAPI
NTSTATUS
NTAPI
RtlRunOnceComplete(
    _Inout_ PRTL_RUN_ONCE RunOnce,
    _In_ ULONG Flags,
    _In_opt_ PVOID Context);

/* Taken from Wine kernel32/sync.c */

/*
 * @implemented
 */
BOOL NTAPI InitOnceExecuteOnce( INIT_ONCE *once, PINIT_ONCE_FN func, void *param, void **context )
{
    return !RtlRunOnceExecuteOnce( once, (PRTL_RUN_ONCE_INIT_FN)func, param, context );
}

BOOL
WINAPI
InitOnceBeginInitialize(
    LPINIT_ONCE lpInitOnce,
    DWORD dwFlags,
    PBOOL fPending,
    LPVOID* lpContext)

{
    NTSTATUS Status;

    Status = RtlRunOnceBeginInitialize(lpInitOnce, dwFlags, lpContext);
    if (!NT_SUCCESS(Status))
    {
        RtlSetLastWin32Error(RtlNtStatusToDosError(Status));
        return FALSE;
    }

    *fPending = (Status == STATUS_PENDING);
    return TRUE;
}

BOOL
WINAPI
InitOnceComplete(LPINIT_ONCE lpInitOnce, DWORD dwFlags, LPVOID lpContext)
{
    NTSTATUS Status;

    Status = RtlRunOnceComplete(lpInitOnce, dwFlags, lpContext);
    if (!NT_SUCCESS(Status))
    {
        RtlSetLastWin32Error(RtlNtStatusToDosError(Status));
        return FALSE;
    }

    return TRUE;
}
