#include "ffta.h"

/* Target: complete [0x08142D34, 0x08142E10), 220 bytes, 97 instructions,
 * six literal words and one padding halfword:
 * f0b582b0021c0e1c51680091106801906a460c1c0003050bd3885804430dd279d0097060002b
 * 25d12943002902d10220306049e00d48b060230e2a02191c114320020d1c041c032030600948
 * 854229d8071ce30f6a00191c114360000d1c041cb0680138b060bd42f3d91be002fcffffffff
 * ff0f0448834217d12943002905d10420306020e00000ff070000802212030020291c11400143
 * 002902d00120306000e03160f46035610ee009495818b06003203060230e2a02191c11432002
 * 054a054b1943f060316102b0f0bc01bc004701fcffff0000000000000010
 *
 * libgcc dp-bit unpack_d (FLOAT_BIT_ORDER_MISMATCH, FLOAT_WORD_ORDER_MISMATCH),
 * built with its library unit's old_agbcc -mthumb-interwork -O2.  agbcc leaves
 * 0x08142D4C/4E/52/54 in r0: its s_register_operand rejects (subreg (mem)), so
 * combine does not fold the ldrh/ldrb into the shifts.
 */
typedef unsigned long long Fraction08142D34;

typedef union {
    double value;
    u32 words[2];
    struct {
        Fraction08142D34 fraction : 52;
        u32 exponent : 11;
        u32 sign : 1;
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

void func_08142D34(const EncodedDouble08142D34 *source,
                   NumberParts08142D34 *parts)
{
    Fraction08142D34 fraction;
    s32 exponent;
    s32 sign;
    EncodedDouble08142D34 swapped;

    swapped.words[0] = source->words[1];
    swapped.words[1] = source->words[0];
    /* The fields are read through one pointer register that first holds the
     * source (adds r2, r0 at 0x08142D38) and then the swapped copy
     * (mov r2, sp at 0x08142D44). */
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
