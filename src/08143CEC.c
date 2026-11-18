#include "ffta.h"

/* __mulsf3 from libgcc fp-bit.c, GCC 2.95, as distributed with agbcc.
 * Copyright (C) 1994-1998 Free Software Foundation, Inc.
 * SPDX-License-Identifier: GPL-2.0-or-later WITH GCC-exception-2.0
 */
typedef enum {
    CLASS_SNAN,
    CLASS_QNAN,
    CLASS_ZERO,
    CLASS_NUMBER,
    CLASS_INFINITY
} fp_class_type;

typedef struct {
    fp_class_type class;
    u32 sign;
    s32 normal_exp;
    u32 fraction;
} fp_number_type;

extern fp_number_type data_03005E68;
extern void func_08143A84(const float *, fp_number_type *);
extern float func_081439C8(fp_number_type *);

static inline int isnan(fp_number_type *x)
{
    return x->class == CLASS_SNAN || x->class == CLASS_QNAN;
}

static inline int isinf(fp_number_type *x)
{
    return x->class == CLASS_INFINITY;
}

static inline int iszero(fp_number_type *x)
{
    return x->class == CLASS_ZERO;
}

static inline fp_number_type *multiply_parts(fp_number_type *a, fp_number_type *b,
                                             fp_number_type *tmp)
{
    u32 low = 0;
    u32 high = 0;

    if (isnan(a)) {
        a->sign = a->sign != b->sign;
        return a;
    }
    if (isnan(b)) {
        b->sign = a->sign != b->sign;
        return b;
    }
    if (isinf(a)) {
        if (iszero(b))
            return &data_03005E68;
        a->sign = a->sign != b->sign;
        return a;
    }
    if (isinf(b)) {
        if (iszero(a))
            return &data_03005E68;
        b->sign = a->sign != b->sign;
        return b;
    }
    if (iszero(a)) {
        a->sign = a->sign != b->sign;
        return a;
    }
    if (iszero(b)) {
        b->sign = a->sign != b->sign;
        return b;
    }

    {
        long long product = (long long)a->fraction * (long long)b->fraction;
        high = product >> 32;
        low = product;
    }
    tmp->normal_exp = a->normal_exp + b->normal_exp;
    tmp->sign = a->sign != b->sign;
    tmp->normal_exp += 2;
    while (high >= (1LL << 31)) {
        tmp->normal_exp++;
        if (high & 1) {
            low >>= 1;
            low |= 0x80000000;
        }
        high >>= 1;
    }
    while (high < (1LL << 30)) {
        tmp->normal_exp--;
        high <<= 1;
        if (low & 0x80000000)
            high |= 1;
        low <<= 1;
    }
    if ((high & 0x7f) == 0x40) {
        if (high & (1 << 7))
            high += 0x40;
        else if (low)
            high += 0x40;
    }
    tmp->fraction = high;
    tmp->class = CLASS_NUMBER;
    return tmp;
}

float func_08143CEC(float arg_a, float arg_b)
{
    fp_number_type a, b, tmp;
    fp_number_type *result;

    func_08143A84(&arg_a, &a);
    func_08143A84(&arg_b, &b);
    result = multiply_parts(&a, &b, &tmp);
    return func_081439C8(result);
}
