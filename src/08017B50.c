/* func_08017B50 - 0x08017B50, 22 bytes of code.
 *
 * The indexed span stops at 0x08017B5C, which cuts the function in half; match.py
 * sizes from the ELF symbol, so the full 22 bytes have to come out.  The two
 * zero bytes at 0x08017B66 belong to the next function's alignment.
 *
 * target  00b5 1822 815e 807d 8842 00dd 081c 0004 000c 02bc 0847
 *
 * Clamps an unsigned byte against a signed halfword: 0x08017B68 and
 * 0x08017B9C do the same clamp against +0x18 and +0x1A of the same record,
 * and 0x08017BE8 reads +0x18 as a plain u16.  So +0x18 is the record's HP-like
 * halfword and +0x16 is one of the three bytes just below it (+0x15..+0x17,
 * all read with ldrb elsewhere).  Only those two members are touched here, so
 * only those two are named.
 *
 * The `lsls #16 / lsrs #16` pair after the join is the u16 return: one arm of
 * the merge holds a zero-extended u8 and the other a sign-extended s16, so the
 * conversion to the declared return type lands at the join rather than on
 * either arm.
 */

#include "ffta.h"

typedef struct {
    u8 unknown_00[0x16];  /* +0x00 .. +0x15 */
    u8 value_16;          /* +0x16 */
    s16 value_18;         /* +0x18 */
} Struct08017B50;

u16 func_08017B50(Struct08017B50 *state) {
    s16 limit = state->value_18;
    u8 value = state->value_16;
    return value > limit ? limit : value;
}