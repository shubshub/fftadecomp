#include "dp_bit.h"

extern fp_number_type *func_08142E10(fp_number_type *first,
                                     fp_number_type *second,
                                     fp_number_type *result);

/* Target 0x08143080, 52 bytes: 10b593b00f901091119212930fa86946fff750fe11a805ac211cfff74bfe0aaa6846211cfff7b4fefff79efd13b010bc04bc1047 */
double func_08143080(double first, double second)
{
    fp_number_type first_expanded;
    fp_number_type second_expanded;
    fp_number_type result;

    func_08142D34((const encoded_double *)&first, &first_expanded);
    func_08142D34((const encoded_double *)&second, &second_expanded);
    return func_08142BE8(func_08142E10(&first_expanded,
                                     &second_expanded, &result));
}
