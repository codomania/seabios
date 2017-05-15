// Code to detect whether SEV is enabled
// 
// Copyright (C) 2017  Brijesh Singh, AMD Inc.
//

#include "sev.h"
#include "x86.h"
#include "output.h" // dprintf

void sev_detect(void)
{
    unsigned int eax, ebx, ecx, edx;
    unsigned long val;

    //
    // Check if 0x8000_001F leaf exit
    //
    cpuid(0x80000000, &eax, &ebx, &ecx, &edx);
    if (eax < 0x8000001f)
        return;

    //
    // Check SEV feature is supported
    //  Fn8000_001F[EAX] Bit 1 - SEV supported
    //
    cpuid(0x8000001f, &eax, &ebx, &ecx, &edx);
    if (!(eax & 2))
        return;


    //
    // Check SEV is enabled
    // MSR 0xc000_0010 Bit 0 - SEV enabled
    //
    val = rdmsr(0xc0010131);
    if (!(val & 1))
        return;

    has_sev = 1;
    dprintf(1, "SEV is enabled\n");
}
