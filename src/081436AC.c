#include "dp_bit.h"

static inline int is_nan(const fp_number_type *parts)
{
    return parts->class == 0 || parts->class == 1;
}

s32 func_081436AC(double first, double second)
{
    fp_number_type first_parts;
    fp_number_type second_parts;

    func_08142D34((const encoded_double *)&first, &first_parts);
    func_08142D34((const encoded_double *)&second, &second_parts);
    if (is_nan(&first_parts) || is_nan(&second_parts))
        return 1;
    return func_08143528(&first_parts, &second_parts);
}
