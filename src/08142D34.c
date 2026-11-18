#include "dp_bit.h"

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
void func_08142D34(const encoded_double *source,
                   fp_number_type *parts)
{
    fractype fraction;
    s32 exponent;
    s32 sign;
    encoded_double swapped;

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
            parts->class = CLASS_ZERO;
        else {
            parts->normal_exp = exponent - 1023 + 1;
            fraction <<= 8;
            parts->class = CLASS_NUMBER;
            while (fraction < ((fractype)1 << 60)) {
                fraction <<= 1;
                parts->normal_exp--;
            }
            parts->fraction.ll = fraction;
        }
    } else if (exponent == 0x7ff) {
        if (fraction == 0)
            parts->class = CLASS_INFINITY;
        else {
            if (fraction & ((fractype)1 << 51))
                parts->class = CLASS_QNAN;
            else
                parts->class = CLASS_SNAN;
            parts->fraction.ll = fraction;
        }
    } else {
        parts->normal_exp = exponent - 1023;
        parts->class = CLASS_NUMBER;
        parts->fraction.ll = (fraction << 8) | ((fractype)1 << 60);
    }
}
