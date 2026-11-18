#include "dp_bit.h"

/* Five observed words shared by the unpack and comparison interfaces. */
/* Conditional views from the complete entries and the by-value root transport. */

s32 func_0814362C(double first, double second)
{
    fp_number_type first_number;
    fp_number_type second_number;

    func_08142D34((const encoded_double *)&first, &first_number);
    func_08142D34((const encoded_double *)&second, &second_number);
    return func_08143528(&first_number, &second_number);
}
