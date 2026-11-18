#include "dp_bit.h"

float func_08144314(u32 kind, u32 sign, s32 exponent, u32 fraction);

float func_08143980(double value)
{
    fp_number_type parts;
    u32 fraction;

    func_08142D34((const encoded_double *)&value, &parts);
    fraction = parts.fraction.ll >> 30;
    if (parts.fraction.ll & 0x3FFFFFFFULL)
        fraction |= 1;
    return func_08144314(parts.class, parts.sign, parts.normal_exp, fraction);
}
