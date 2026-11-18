#include "ffta.h"

/* __fixunsdfsi from agbcc's libgcc2.c, built with 32-bit long.
 * Copyright (C) 1989, 1992-1998 Free Software Foundation, Inc.
 * SPDX-License-Identifier: GPL-2.0-or-later WITH GCC-exception-2.0
 */
u32 func_08142864(double value)
{
    if (value >= 2147483648.0)
        return (u32)(s32)(value + -2147483648.0) + 0x80000000u;
    return (s32)value;
}
