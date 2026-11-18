#include "dp_bit.h"

/* Target: complete [0x081438BC, 0x08143930), 116 bytes. */

static inline int iszero(fp_number_type *number)
{
    return number->class == CLASS_ZERO;
}

static inline int isnan(fp_number_type *number)
{
    return number->class == CLASS_SNAN || number->class == CLASS_QNAN;
}

static inline int isinf(fp_number_type *number)
{
    return number->class == CLASS_INFINITY;
}

s32 func_081438BC(double value)
{
    fp_number_type number;
    s32 result;

    func_08142D34((const encoded_double *)&value, &number);
    if (iszero(&number))
        return 0;
    if (isnan(&number))
        return 0;
    if (isinf(&number))
        return number.sign ? (-0x7FFFFFFF - 1) : 0x7FFFFFFF;
    if (number.normal_exp < 0)
        return 0;
    if (number.normal_exp > 30)
        return number.sign ? (-0x7FFFFFFF - 1) : 0x7FFFFFFF;

    result = number.fraction.ll >> (60 - number.normal_exp);
    return number.sign ? -result : result;
}
