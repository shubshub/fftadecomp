#include "ffta.h"

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

/* Conditional interfaces from the complete unpack, combine and pack entries. */
extern void func_08142D34(const double *value, fp_number_type *number);
extern fp_number_type *func_08142E10(fp_number_type *first,
                                     fp_number_type *second,
                                     fp_number_type *result);
extern double func_08142BE8(fp_number_type *number);

double func_081430B4(double first, double second)
{
    fp_number_type first_number;
    fp_number_type second_number;
    fp_number_type result;

    func_08142D34(&first, &first_number);
    func_08142D34(&second, &second_number);
    second_number.sign ^= 1;
    return func_08142BE8(func_08142E10(&first_number, &second_number, &result));
}
