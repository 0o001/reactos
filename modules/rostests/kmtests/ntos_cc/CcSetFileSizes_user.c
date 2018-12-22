/*
 * PROJECT:         ReactOS kernel-mode tests
 * LICENSE:         GPLv2+ - See COPYING in the top level directory
 * PURPOSE:         Kernel-Mode Test Suite CcSetFileSizes test user-mode part
 * PROGRAMMER:      Pierre Schweitzer <pierre@reactos.org>
 */

#include <kmt_test.h>

#define IOCTL_START_TEST  1
#define IOCTL_FINISH_TEST 2

START_TEST(CcSetFileSizes)
{
    DWORD Ret;
    ULONG TestId;

    KmtLoadDriver(L"CcSetFileSizes", FALSE);
    KmtOpenDriver();

    /* 0: mapped data
     * 1: copy read
     */
    for (TestId = 0; TestId < 2; ++TestId)
    {
        Ret = KmtSendUlongToDriver(IOCTL_START_TEST, TestId);
        ok(Ret == ERROR_SUCCESS, "KmtSendUlongToDriver failed: %lx\n", Ret);
        Ret = KmtSendUlongToDriver(IOCTL_FINISH_TEST, TestId);
        ok(Ret == ERROR_SUCCESS, "KmtSendUlongToDriver failed: %lx\n", Ret);
    }

    KmtCloseDriver();
    KmtUnloadDriver();
}
