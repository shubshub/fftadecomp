#include "dp_bit.h"

static inline s32 number_is_nan(const fp_number_type *number)
{
    s32 result = 0;

    if (number->class <= 1)
        result = 1;
    return result;
}

/* Complete target: 0x081436FC..0x0814374C, 80 bytes. */
s32 func_081436FC(double first, double second)
{
    fp_number_type first_parts;
    fp_number_type second_parts;

    func_08142D34((const encoded_double *)&first, &first_parts);
    func_08142D34((const encoded_double *)&second, &second_parts);
    if (number_is_nan(&first_parts) || number_is_nan(&second_parts))
        return -1;
    return func_08143528(&first_parts, &second_parts);
}
