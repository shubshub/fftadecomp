#include "ffta.h"

/* Complete [0x080DD4D4, 0x080DD50C): 56 bytes, 25 instructions, one literal
 * word (0x7FFF) after two alignment bytes.
 * 10b5021c9489012020400a49002800d0d18b080403140748834205d102202040191c0028
 * 00d0118c0804001410bc02bc08470000ff7f0000
 */

/* The flags word and the halfword fields of src/080DD50C.c, src/080DD52C.c
 * and src/080DD54C.c, which return the field for flag bit 1, 2 or 3 and
 * 0x7FFF when the bit is clear. */
typedef struct {
    u8 unknown_00[0x0C];
    u16 flags;
    u8 unknown_0e[0x10];
    s16 value_1e;
    s16 value_20;
} State080DD4D4;

/* The first of field +0x1E (flag bit 0) and field +0x20 (flag bit 1) that is
 * present and not 0x7FFF; 0x7FFF when neither is.  The second step repeats
 * the expression func_080DD50C returns. */
s16 func_080DD4D4(const State080DD4D4 *state)
{
    s16 value = (state->flags & 1) ? state->value_1e : 0x7FFF;

    if (value == 0x7FFF)
        value = (state->flags & 2) ? state->value_20 : 0x7FFF;
    return value;
}
