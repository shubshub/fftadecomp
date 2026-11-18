#include "dp_bit.h"

/* Conditional interfaces from the complete incoming accesses of both helpers. */

/* Shared classification predicate from the published comparison family. */
static inline s32 number_is_nan(const fp_number_type *number)
{
    s32 result = 0;

    if (number->class <= 1)
        result = 1;
    return result;
}

/* Complete [0x081437EC,0x0814383A): 78 bytes.
 * Each incoming eight-byte value is passed by address to the unpack helper.
 * The five observed output words form each20-byte comparison record.
 * Conditional transport only, no numeric result or complete initialization,
 * helper effects, readability, bounds or termination theorem asserted.
 */
s32 func_081437EC(double first, double second)
{
    fp_number_type first_number;
    fp_number_type second_number;

    func_08142D34((const encoded_double *)&first, &first_number);
    func_08142D34((const encoded_double *)&second, &second_number);
    if (number_is_nan(&first_number) || number_is_nan(&second_number))
        return 1;
    return func_08143528(&first_number, &second_number);
}
