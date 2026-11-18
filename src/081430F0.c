#include "dp_bit.h"

/* libgcc dp-bit.c, _fpmul_parts and __muldf3.
 * GPL-2.0-or-later with the libgcc exception. */
extern fp_number_type data_03005E50;

#define IMPLICIT_1 (1LL << 60)
#define IMPLICIT_2 (1LL << 61)
#define FRACHIGH 0x8000000000000000LL
#define NGARDS 8L
#define GARDMASK 0xff
#define GARDMSB 0x80
#define GARDROUND 0x7f

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
    fractype low = 0;
    fractype high = 0;

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
            return &data_03005E50;
        a->sign = a->sign != b->sign;
        return a;
    }
    if (isinf(b)) {
        if (iszero(a))
            return &data_03005E50;
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

    /* Form the 128-bit product from four 32-bit limb products. */
    {
        fractype nl = a->fraction.ll & 0xffffffff;
        fractype nh = a->fraction.ll >> 32;
        fractype ml = b->fraction.ll & 0xffffffff;
        fractype mh = b->fraction.ll >> 32;
        fractype pp_ll = ml * nl;
        fractype pp_hl = mh * nl;
        fractype pp_lh = ml * nh;
        fractype pp_hh = mh * nh;
        fractype res2 = 0;
        fractype res0 = 0;
        fractype cross = pp_hl + pp_lh;

        if (cross < pp_hl)
            res2 += 0x100000000LL;
        pp_hl = (cross << 32) & 0xffffffff00000000LL;
        res0 = pp_ll + pp_hl;
        if (res0 < pp_ll)
            res2++;
        res2 += ((cross >> 32) & 0xffffffffL) + pp_hh;
        high = res2;
        low = res0;
    }

    tmp->normal_exp = a->normal_exp + b->normal_exp;
    tmp->sign = a->sign != b->sign;
    tmp->normal_exp += 4;
    while (high >= IMPLICIT_2) {
        tmp->normal_exp++;
        if (high & 1) {
            low >>= 1;
            low |= FRACHIGH;
        }
        high >>= 1;
    }
    while (high < IMPLICIT_1) {
        tmp->normal_exp--;
        high <<= 1;
        if (low & FRACHIGH)
            high |= 1;
        low <<= 1;
    }
    /* Resolve halfway cases before the packer discards the guard bits. */
    if ((high & GARDMASK) == GARDMSB) {
        if (high & (1 << NGARDS))
            high += GARDROUND + 1;
        else if (low)
            high += GARDROUND + 1;
    }
    tmp->fraction.ll = high;
    tmp->class = CLASS_NUMBER;
    return tmp;
}

double func_081430F0(double first, double second)
{
    fp_number_type a;
    fp_number_type b;
    fp_number_type tmp;
    fp_number_type *result;

    func_08142D34((const encoded_double *)&first, &a);
    func_08142D34((const encoded_double *)&second, &b);
    result = multiply_parts(&a, &b, &tmp);
    return func_08142BE8(result);
}
