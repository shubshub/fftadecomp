#include "ffta.h"

/* __floatdidf from agbcc's libgcc2.c, [0x081428E4, 0x08142950).
 * Copyright (C) 1989, 1992-1998 Free Software Foundation, Inc.
 * SPDX-License-Identifier: GPL-2.0-or-later WITH GCC-exception-2.0
 */
#define WORD_SIZE (sizeof(s32) * 8)
#define HIGH_HALFWORD_COEFF (1ULL << (WORD_SIZE / 2))
#define HIGH_WORD_COEFF (1ULL << WORD_SIZE)

double func_081428E4(long long value)
{
    double result;

    result = (s32)(value >> WORD_SIZE);
    result *= HIGH_HALFWORD_COEFF;
    result *= HIGH_HALFWORD_COEFF;
    result += (u32)(value & (HIGH_WORD_COEFF - 1));
    return result;
}
