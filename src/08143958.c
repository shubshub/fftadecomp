#include "ffta.h"

/* libgcc dp-bit.c, __make_dp. GPL-2.0-or-later with the libgcc exception. */
typedef unsigned long long fractype;
typedef u32 halffractype;

typedef enum {
    CLASS_SNAN,
    CLASS_QNAN,
    CLASS_ZERO,
    CLASS_NUMBER,
    CLASS_INFINITY
} fp_class_type;

typedef struct {
    fp_class_type class;
    u32 sign;
    s32 normal_exp;
    union {
        fractype ll;
        halffractype l[2];
    } fraction;
} fp_number_type;

extern double func_08142BE8(fp_number_type *number);

double func_08143958(fp_class_type classification, u32 sign, s32 exponent, fractype fraction)
{
    fp_number_type number;

    number.class = classification;
    number.sign = sign;
    number.normal_exp = exponent;
    number.fraction.ll = fraction;
    return func_08142BE8(&number);
}
