/* 0x0802AB64 - 176 bytes (the index calls it 50: the scanner stopped at the
 * `beq` at 0x0802AB94, which always falls through.  The body runs on to the
 * interworking return at 0x0802AC12; the next prologue is at 0x0802AC14).
 *
 * Fills two runs of u16 entries in `state->base`, `count` entries each, the
 * second run starting `offset` entries after the first.  The high nibble of
 * every entry is a 4-bit tag; the low twelve bits are the value.
 *
 * The last argument picks the layout:
 *
 *   flag != 0  the two runs interleave - run 1 takes the even values and run 2
 *              the odd ones - and the tag comes from the state block;
 *   flag == 0  run 1 takes the first `count` values and run 2 the next
 *              `count`, and the tag comes from the sixth argument.
 *
 * The sixth argument is a u16 but the callers only ever fill its low byte
 * with the same tag byte the state block holds at +0x1F, so the two paths
 * agree on the high nibble.
 *
 * The parameters are narrowed in the prologue, not at their use: `lsls/lsrs
 * #16` on the two u16 arguments and `lsls/lsrs #24` on the u8 ones.  The
 * value argument is copied into a local before the loops, which is why the
 * ROM materialises that copy after the parameter setup instead of with it.
 *
 * There is no literal pool; every constant is immediate.
 *
 * Target bytes:
 *   f0b557464e464546e0b4071c0898099c0a9d0904090c894612041b061b0e9846
 *   0006060e2404240c2d06120c9446002d1cd00025301c854233d2fc6848464219
 *   53001b1969006144f87f0003084318804244520012190131f87f000301431180
 *   681c0004050cb542e8d31ae00025301c854216d2fb68240382464f4679194a00
 *   d218674678192043108041444900c918a819604420430880681c0004050c5545
 *   ebd338bc9846a146aa46f0bc01bc0047
 */

#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0c];
    u16 *base;
    u8 unknown_10[0x0f];
    u8 tag;
} State0802AB64;

void func_0802AB64(State0802AB64 *state, u16 index, u16 value, u8 offset,
                   u8 count, u16 tag, u8 flag)
{
    u16 i;
    u16 v = value;

    if (flag) {
        for (i = 0; i < count; i++) {
            state->base[index + i] = (v + i * 2) | (state->tag << 12);
            state->base[index + i + offset] = (v + i * 2 + 1) | (state->tag << 12);
        }
    } else {
        for (i = 0; i < count; i++) {
            state->base[index + i] = (v + i) | (tag << 12);
            state->base[index + i + offset] = (count + i + v) | (tag << 12);
        }
    }
}
