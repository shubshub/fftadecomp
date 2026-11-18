#include "dp_bit.h"

/* Target: complete [0x0814379C, 0x081437EA), 78 bytes. */

static inline s32 number_is_nan(const fp_number_type *number)
{
    s32 result = 0;

    if (number->class <= 1)
        result = 1;
    return result;
}

s32 func_0814379C(double first, double second)
{
    fp_number_type first_number;
    fp_number_type second_number;

    func_08142D34((const encoded_double *)&first, &first_number);
    func_08142D34((const encoded_double *)&second, &second_number);
    if (number_is_nan(&first_number) || number_is_nan(&second_number))
        return 1;
    return func_08143528(&first_number, &second_number);
}
