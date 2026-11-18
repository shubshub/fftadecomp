#ifndef FFTA_DP_BIT_H
#define FFTA_DP_BIT_H

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

typedef union {
    double value;
    u32 words[2];
    struct {
        fractype fraction : 52;
        u32 exponent : 11;
        u32 sign : 1;
    } fields;
} encoded_double;

double func_08142BE8(fp_number_type *parts);
void func_08142D34(const encoded_double *value, fp_number_type *parts);
s32 func_08143528(const fp_number_type *first, const fp_number_type *second);

#endif
