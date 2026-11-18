#include "dp_bit.h"

/* Target: complete [0x08143528, 0x0814362A), 258 bytes, 129 instructions. */
static inline s32 number_is_nan(const fp_number_type *number)
{
    s32 result = 0;

    if (number->class <= 1)
        result = 1;
    return result;
}

static inline s32 number_is_infinite(const fp_number_type *number)
{
    s32 result = 0;

    if (number->class == 4)
        result = 1;
    return result;
}

static inline s32 number_is_zero(const fp_number_type *number)
{
    s32 result = 0;

    if (number->class == 2)
        result = 1;
    return result;
}

s32 func_08143528(const fp_number_type *first, const fp_number_type *second)
{
    if (number_is_nan(first) || number_is_nan(second))
        return 1;
    if (number_is_infinite(first) && number_is_infinite(second))
        return second->sign - first->sign;
    if (number_is_infinite(first))
        return first->sign ? -1 : 1;
    if (number_is_infinite(second))
        return second->sign ? 1 : -1;
    if (number_is_zero(first) && number_is_zero(second))
        return 0;
    if (number_is_zero(first))
        return second->sign ? 1 : -1;
    if (number_is_zero(second))
        return first->sign ? -1 : 1;
    if (first->sign != second->sign)
        return first->sign ? -1 : 1;
    if (first->normal_exp > second->normal_exp)
        return first->sign ? -1 : 1;
    if (first->normal_exp < second->normal_exp)
        return first->sign ? 1 : -1;
    if (first->fraction.l[1] > second->fraction.l[1] ||
        (first->fraction.l[1] == second->fraction.l[1] &&
         first->fraction.l[0] > second->fraction.l[0]))
        return first->sign ? -1 : 1;
    if (second->fraction.l[1] > first->fraction.l[1] ||
        (second->fraction.l[1] == first->fraction.l[1] &&
         second->fraction.l[0] > first->fraction.l[0]))
        return first->sign ? 1 : -1;
    return 0;
}
