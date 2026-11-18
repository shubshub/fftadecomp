#include "dp_bit.h"

/* Complete target 0x0814339C..0x08143528, 396 bytes.
 * The two helper entries establish two-word value transport and the decoded
 * fields at offsets 0, 4, 8, 12 and 16. Their numerical correctness and the
 * contents of the selected exceptional-value record are not assumed here.
 */
extern fp_number_type data_03005E50;

static inline int is_nan_0814339C(const fp_number_type *value)
{
    return value->class == CLASS_SNAN ||
           value->class == CLASS_QNAN;
}

static inline int is_infinite_0814339C(const fp_number_type *value)
{
    return value->class == CLASS_INFINITY;
}

static inline int is_zero_0814339C(const fp_number_type *value)
{
    return value->class == CLASS_ZERO;
}

/* The decoded calculation selects the record passed to the common pack call. */
static inline fp_number_type *divide_parts_0814339C(
    fp_number_type *first, fp_number_type *second)
{
    fractype dividend;
    fractype divisor;
    fractype bit;
    fractype quotient;

    if (is_nan_0814339C(first))
        return first;
    if (is_nan_0814339C(second))
        return second;

    first->sign ^= second->sign;
    if (is_infinite_0814339C(first) || is_zero_0814339C(first)) {
        if (first->class == second->class)
            return &data_03005E50;
        return first;
    }
    if (is_infinite_0814339C(second)) {
        first->fraction.ll = 0;
        first->normal_exp = 0;
        return first;
    }
    if (is_zero_0814339C(second)) {
        first->class = CLASS_INFINITY;
        return first;
    }

    first->normal_exp -= second->normal_exp;
    dividend = first->fraction.ll;
    divisor = second->fraction.ll;
    if (dividend < divisor) {
        dividend <<= 1;
        first->normal_exp--;
    }
    bit = (fractype)1 << 60;
    quotient = 0;
    while (bit != 0) {
        if (dividend >= divisor) {
            quotient |= bit;
            dividend -= divisor;
        }
        bit >>= 1;
        dividend <<= 1;
    }

    if ((quotient & 0xFF) == 0x80 &&
        ((quotient & 0x100) != 0 || dividend != 0))
        quotient += 0x80;
    first->fraction.ll = quotient;
    return first;
}

double func_0814339C(double numerator, double denominator)
{
    fp_number_type first;
    fp_number_type second;

    func_08142D34((const encoded_double *)&numerator, &first);
    func_08142D34((const encoded_double *)&denominator, &second);
    return func_08142BE8(divide_parts_0814339C(&first, &second));
}
