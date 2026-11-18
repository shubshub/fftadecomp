#include "ffta.h"

/* 0x08142BE8..0x08142D34: 332 bytes, 139 instructions, including the literal
 * pools.  libgcc dp-bit.c pack_d (gcc 2.95 config/fp-bit.c, as shipped in
 * agbcc libgcc/fp-bit-base.c) with FLOAT_BIT_ORDER_MISMATCH and
 * FLOAT_WORD_ORDER_MISMATCH; GPL-2.0-or-later with the libgcc exception.
 * f0b582b0011ccc680d694f68002600220868012800d80122002a0dd0034e044a044b201c291c
 * 194362e00000ff07000000000000000008000022042800d10122002a23d10022022800d10122
 * 002a02d0002400254ee0281c204300284ad08a68044882420fda821a382a05dd0024002539e0
 * 000002fcffff291c201c01f088fb0d1c041c2fe00348824207dd024e002400252fe0ff030000
 * ff07000009481618ff20211c0140002280290dd1002a0bd10130211c0140101c0843002808d0
 * 8020002103e0ff0300007f20002124184d411948854207d9eb076208181c104369080d1c041c
 * 01362b06220a181c1043290a0d1c041c0094114a2a40019810490840104301906a460f49081c
 * 064031010e48d38818400843d080f9017f20d37918400843d071009901980090019100980199
 * 02b0f0bc04bc1047ffffff1fffff0f000000f0ffff0700000f80ffff
 */
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
    fractype value_raw;
    halffractype words[2];
    struct {
        fractype fraction : 52 __attribute__((packed));
        u32 exp : 11 __attribute__((packed));
        u32 sign : 1 __attribute__((packed));
    } bits;
} FLO_union_type;

#define EXPBIAS 1023
#define EXPMAX 0x7FF
#define NORMAL_EXPMIN (-EXPBIAS + 1)
#define FRAC_NBITS 64
#define NGARDS 8
#define GARDROUND 0x7F
#define GARDMASK 0xFF
#define GARDMSB 0x80
#define QUIET_NAN 0x8000000000000LL
#define IMPLICIT_2 (1LL << 61)

static inline int isnan(fp_number_type *x)
{
    return x->class == CLASS_SNAN || x->class == CLASS_QNAN;
}

static inline int isinf(fp_number_type *x)
{
    return x->class == CLASS_INFINITY;
}

static inline int iszero(fp_number_type *x)
{
    return x->class == CLASS_ZERO;
}

double func_08142BE8(fp_number_type *src)
{
    FLO_union_type dst;
    fractype fraction = src->fraction.ll;
    int sign = src->sign;
    int exp = 0;

    if (isnan(src)) {
        exp = EXPMAX;
        fraction |= QUIET_NAN;
    } else if (isinf(src)) {
        exp = EXPMAX;
        fraction = 0;
    } else if (iszero(src)) {
        exp = 0;
        fraction = 0;
    } else if (fraction == 0) {
        exp = 0;
    } else {
        if (src->normal_exp < NORMAL_EXPMIN) {
            int shift = NORMAL_EXPMIN - src->normal_exp;

            exp = 0;
            if (shift > FRAC_NBITS - NGARDS)
                fraction = 0;
            else
                fraction >>= shift;
            fraction >>= NGARDS;
        } else if (src->normal_exp > EXPBIAS) {
            exp = EXPMAX;
            fraction = 0;
        } else {
            exp = src->normal_exp + EXPBIAS;
            if ((fraction & GARDMASK) == GARDMSB) {
                if (fraction & (1 << NGARDS))
                    fraction += GARDROUND + 1;
            } else {
                fraction += GARDROUND;
            }
            if (fraction >= IMPLICIT_2) {
                fraction >>= 1;
                exp += 1;
            }
            fraction >>= NGARDS;
        }
    }

    dst.bits.fraction = fraction;
    dst.bits.exp = exp;
    dst.bits.sign = sign;

    {
        halffractype tmp = dst.words[0];
        dst.words[0] = dst.words[1];
        dst.words[1] = tmp;
    }

    return dst.value;
}
