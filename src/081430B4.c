#include "dp_bit.h"

extern fp_number_type *func_08142E10(fp_number_type *first,
                                     fp_number_type *second,
                                     fp_number_type *result);

double func_081430B4(double first, double second)
{
    fp_number_type first_number;
    fp_number_type second_number;
    fp_number_type result;

    func_08142D34((const encoded_double *)&first, &first_number);
    func_08142D34((const encoded_double *)&second, &second_number);
    second_number.sign ^= 1;
    return func_08142BE8(func_08142E10(&first_number, &second_number, &result));
}
