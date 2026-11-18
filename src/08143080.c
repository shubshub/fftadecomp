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

extern void func_08142D34(const double *value, fp_number_type *expanded);
extern fp_number_type *func_08142E10(fp_number_type *first,
                                     fp_number_type *second,
                                     fp_number_type *result);
extern double func_08142BE8(fp_number_type *expanded);

/* Target 0x08143080, 52 bytes: 10b593b00f901091119212930fa86946fff750fe11a805ac211cfff74bfe0aaa6846211cfff7b4fefff79efd13b010bc04bc1047 */
double func_08143080(double first, double second)
{
    fp_number_type first_expanded;
    fp_number_type second_expanded;
    fp_number_type result;

    func_08142D34(&first, &first_expanded);
    func_08142D34(&second, &second_expanded);
    return func_08142BE8(func_08142E10(&first_expanded,
                                     &second_expanded, &result));
}
