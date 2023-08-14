/*
 * PROJECT:         ReactOS api tests
 * LICENSE:         LGPLv2.1+ - See COPYING.LIB in the top level directory
 * PURPOSE:         Test for Rtl Critical Section API
 * PROGRAMMERS:     Thomas Faber <thomas.faber@reactos.org>
 */

#include "precomp.h"

typedef
NTSTATUS
NTAPI
FN_InitializeCriticalSectionEx(
    _Out_ PRTL_CRITICAL_SECTION CriticalSection,
    _In_ ULONG SpinCount,
    _In_ ULONG Flags);

FN_InitializeCriticalSectionEx* pfnInitializeCriticalSectionEx;
RTL_CRITICAL_SECTION CritSect;
HANDLE hEventThread1Ready, hEventThread1Cont;
HANDLE hEventThread2Ready, hEventThread2Cont;

DWORD
WINAPI
ThreadProc1(
    _In_ LPVOID lpParameter)
{
    RtlEnterCriticalSection(&CritSect);

    SetEvent(hEventThread1Ready);

    WaitForSingleObject(hEventThread1Cont, INFINITE);

    RtlLeaveCriticalSection(&CritSect);

    return 0;
}

DWORD
WINAPI
ThreadProc2(
    _In_ LPVOID lpParameter)
{
    printf("ThreadProc2 starting\n");
    RtlEnterCriticalSection(&CritSect);

    SetEvent(hEventThread2Ready);

    WaitForSingleObject(hEventThread2Cont, INFINITE);

    RtlLeaveCriticalSection(&CritSect);

    return 0;
}


START_TEST(RtlCriticalSection)
{
    DWORD dwThreadId1, dwThreadId2;

    RtlInitializeCriticalSection(&CritSect);
    ok_long(CritSect.LockCount, -1);
    ok_long(CritSect.RecursionCount, 0);
    ok_ptr(CritSect.OwningThread, NULL);
    ok_ptr(CritSect.LockSemaphore, NULL);
    ok_size_t(CritSect.SpinCount, 0x20007d0);
    ok(CritSect.DebugInfo == LongToPtr(-1), "DebugInfo is %p\n", CritSect.DebugInfo);
    if ((CritSect.DebugInfo != LongToPtr(-1)) && (CritSect.DebugInfo != NULL))
    {
        ok_int(CritSect.DebugInfo->Type, 0);
        ok_int(CritSect.DebugInfo->CreatorBackTraceIndex, 0);
        ok_int(CritSect.DebugInfo->CreatorBackTraceIndexHigh, 0);
        ok_ptr(CritSect.DebugInfo->CriticalSection, &CritSect);
        ok_ptr(CritSect.DebugInfo->ProcessLocksList.Flink, 0);
        ok_ptr(CritSect.DebugInfo->ProcessLocksList.Blink, 0);
        ok_long(CritSect.DebugInfo->EntryCount, 0);
        ok_long(CritSect.DebugInfo->ContentionCount, 0);
        ok_long(CritSect.DebugInfo->Flags, 0);
        ok_int(CritSect.DebugInfo->SpareWORD, 0);
    }

    // Acquire once
    RtlEnterCriticalSection(&CritSect);
    ok_long(CritSect.LockCount, -2);
    ok_long(CritSect.RecursionCount, 1);
    ok_ptr(CritSect.OwningThread, UlongToHandle(GetCurrentThreadId()));
    ok_ptr(CritSect.LockSemaphore, NULL);
    ok_size_t(CritSect.SpinCount, 0x20007d0);

    // Acquire recursively
    RtlEnterCriticalSection(&CritSect);
    ok_long(CritSect.LockCount, -2);
    ok_long(CritSect.RecursionCount, 2);
    ok_ptr(CritSect.OwningThread, UlongToHandle(GetCurrentThreadId()));
    ok_ptr(CritSect.LockSemaphore, NULL);
    ok_size_t(CritSect.SpinCount, 0x20007d0);

    hEventThread1Ready = CreateEvent(NULL, TRUE, FALSE, NULL);
    hEventThread1Cont = CreateEvent(NULL, TRUE, FALSE, NULL);
    hEventThread2Ready = CreateEvent(NULL, TRUE, FALSE, NULL);
    hEventThread2Cont = CreateEvent(NULL, TRUE, FALSE, NULL);

    // Create thread 1 and wait to it time to try to acquire the critical section
    CreateThread(NULL, 0, ThreadProc1, NULL, 0, &dwThreadId1);
    Sleep(10);

    ok_long(CritSect.LockCount, -6);
    ok_long(CritSect.RecursionCount, 2);
    ok_ptr(CritSect.OwningThread, UlongToHandle(GetCurrentThreadId()));
    ok_ptr(CritSect.LockSemaphore, LongToPtr(-1));
    ok_size_t(CritSect.SpinCount, 0x20007d0);

    // Create thread 2 and wait to it time to try to acquire the critical section
    CreateThread(NULL, 0, ThreadProc2, NULL, 0, &dwThreadId2);
    Sleep(10);

    ok_long(CritSect.LockCount, -10);
    ok_long(CritSect.RecursionCount, 2);
    ok_ptr(CritSect.OwningThread, UlongToHandle(GetCurrentThreadId()));
    ok_ptr(CritSect.LockSemaphore, LongToPtr(-1));
    ok_size_t(CritSect.SpinCount, 0x20007d0);

    RtlLeaveCriticalSection(&CritSect);
    RtlLeaveCriticalSection(&CritSect);

    // Wait until thread 1 has acquired the critical section
    WaitForSingleObject(hEventThread1Ready, INFINITE);

    ok_long(CritSect.LockCount, -6);
    ok_long(CritSect.RecursionCount, 1);
    ok_ptr(CritSect.OwningThread, UlongToHandle(dwThreadId1));
    ok_ptr(CritSect.LockSemaphore, LongToPtr(-1));
    ok_size_t(CritSect.SpinCount, 0x20007cf);

    // Release thread 1, wait for thread 2 to acquire the critical section
    SetEvent(hEventThread1Cont);
    WaitForSingleObject(hEventThread2Ready, INFINITE);

    ok_long(CritSect.LockCount, -2);
    ok_long(CritSect.RecursionCount, 1);
    ok_ptr(CritSect.OwningThread, UlongToHandle(dwThreadId2));
    ok_ptr(CritSect.LockSemaphore, LongToPtr(-1));
    ok_size_t(CritSect.SpinCount, 0x20007cf);

    // Release thread 2
    SetEvent(hEventThread2Cont);
}
