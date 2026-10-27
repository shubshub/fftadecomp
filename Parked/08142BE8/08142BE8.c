/* 08142BE8..08142D34: 332 bytes. Pack an internal binary64 number.
 * Adapted from the GNU libgcc fp-bit pack_d implementation (GPL-2.0-or-later
 * with the original libgcc linking exception). */
typedef unsigned long long Fraction;

typedef enum {
    CLASS_SNAN, CLASS_QNAN, CLASS_ZERO, CLASS_NUMBER, CLASS_INFINITY
} NumberClass;

typedef struct {
    NumberClass class;
    unsigned int sign;
    int normal_exp;
    union {
        Fraction ll;
        unsigned int words[2];
    } fraction;
} Number;

typedef struct {
    Fraction fraction : 52 __attribute__((packed));
    unsigned int exponent : 11 __attribute__((packed));
    unsigned int sign : 1 __attribute__((packed));
} Binary64Fields;

typedef union {
    double value;
    Fraction raw;
    unsigned int words[2];
    Binary64Fields bits;
} Binary64;

static __inline__ int is_nan(Number *number)
{
    return number->class == CLASS_SNAN || number->class == CLASS_QNAN;
}

static __inline__ int is_infinite(Number *number)
{
    return number->class == CLASS_INFINITY;
}

static __inline__ int is_zero(Number *number)
{
    return number->class == CLASS_ZERO;
}

double func_08142BE8(Number *source)
{
    Binary64 result;
    Fraction fraction = source->fraction.ll;
    int sign = source->sign;
    int exponent = 0;

    if (is_nan(source)) {
        exponent = 0x7ff;
        fraction |= 0x8000000000000ULL;
    } else if (is_infinite(source)) {
        exponent = 0x7ff;
        fraction = 0;
    } else if (is_zero(source)) {
        exponent = 0;
        fraction = 0;
    } else if (fraction == 0) {
        exponent = 0;
    } else {
        if (source->normal_exp < -1022) {
            int shift = -1022 - source->normal_exp;
            exponent = 0;
            if (shift > 56)
                fraction = 0;
            else
                fraction >>= shift;
            fraction >>= 8;
        } else if (source->normal_exp > 1023) {
            exponent = 0x7ff;
            fraction = 0;
        } else {
            exponent = source->normal_exp + 1023;
            if ((fraction & 0xff) == 0x80) {
                if (fraction & (1 << 8))
                    fraction += 0x80;
            } else {
                fraction += 0x7f;
            }
            if (fraction >= (1ULL << 61)) {
                fraction >>= 1;
                exponent += 1;
            }
            fraction >>= 8;
        }
    }

    result.bits.fraction = fraction;
    {
        Binary64Fields *fields = &result.bits;
        fields->exponent = exponent;
        fields->sign = sign;
    }
    {
        unsigned int temporary = result.words[0];
        result.words[0] = result.words[1];
        result.words[1] = temporary;
    }
    return result.value;
}
