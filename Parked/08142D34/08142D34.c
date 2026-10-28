#include "ffta.h"

/* Target: complete [0x08142D34, 0x08142E10), 220 bytes. */
typedef unsigned int Fraction08142D34 __attribute__((mode(DI)));

typedef union {
    double value;
    Fraction08142D34 raw;
    u32 words[2];
    struct {
        Fraction08142D34 fraction : 52 __attribute__((packed));
        u32 exponent : 11 __attribute__((packed));
        u32 sign : 1 __attribute__((packed));
    } fields;
} EncodedDouble08142D34;

typedef enum {
    CLASS_SNAN08142D34,
    CLASS_QNAN08142D34,
    CLASS_ZERO08142D34,
    CLASS_NUMBER08142D34,
    CLASS_INFINITY08142D34
} NumberClass08142D34;

typedef struct {
    NumberClass08142D34 number_class;
    u32 sign;
    s32 exponent;
    union {
        Fraction08142D34 ll;
        u32 words[2];
    } fraction;
} NumberParts08142D34;

void func_08142D34(EncodedDouble08142D34 *source,
                   NumberParts08142D34 *parts)
{
    Fraction08142D34 fraction;
    s32 exponent;
    s32 sign;
    EncodedDouble08142D34 swapped;

    swapped.words[0] = source->words[1];
    swapped.words[1] = source->words[0];
    source = &swapped;
    fraction = source->fields.fraction;
    exponent = source->fields.exponent;
    sign = source->fields.sign;
    parts->sign = sign;

    if (exponent == 0) {
        if (fraction == 0)
            parts->number_class = CLASS_ZERO08142D34;
        else {
            parts->exponent = exponent - 1023 + 1;
            fraction <<= 8;
            parts->number_class = CLASS_NUMBER08142D34;
            while (fraction < ((Fraction08142D34)1 << 60)) {
                fraction <<= 1;
                parts->exponent--;
            }
            parts->fraction.ll = fraction;
        }
    } else if (exponent == 0x7ff) {
        if (fraction == 0)
            parts->number_class = CLASS_INFINITY08142D34;
        else {
            if (fraction & ((Fraction08142D34)1 << 51))
                parts->number_class = CLASS_QNAN08142D34;
            else
                parts->number_class = CLASS_SNAN08142D34;
            parts->fraction.ll = fraction;
        }
    } else {
        parts->exponent = exponent - 1023;
        parts->number_class = CLASS_NUMBER08142D34;
        parts->fraction.ll = (fraction << 8) | ((Fraction08142D34)1 << 60);
    }
}
