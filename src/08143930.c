#include "dp_bit.h"

/* Complete indexed owner:0x08143930..0x08143958. */
double func_08143930(double value)
{
    fp_number_type parts;

    func_08142D34((const encoded_double *)&value, &parts);
    parts.sign = !parts.sign;
    return func_08142BE8(&parts);
}
