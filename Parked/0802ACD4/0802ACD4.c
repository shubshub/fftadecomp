/* 0x0802ACD4 - 128 bytes - best attempt, NOT byte exact (115 of 128 bytes,
 * 60 of 64 instructions identical).
 *
 * Fills `count` consecutive u16 entries of `state->base` with the high
 * nibble of a 4-bit tag, preserving the low twelve bits, twice: once at
 * `state->base + c + (a * 2) * state->field_15` and once one row further on
 * (the row stride is state->field_15 u16 entries).
 *
 * The parameters are narrowed in the prologue, not at their use: `lsls/lsrs
 * #16` on the s8 parameter (the value is (u16)(a * 2)), `lsls/lsrs #24` on
 * the two u8 parameters and `lsls #24 / lsrs #23` on the third one (used as
 * (u8)c * 2).  The tag is the third parameter, but 0xFF means "use
 * state->tag" instead.
 *
 * The tag parameter is modified in place (that is what puts the tag in r9/sb
 * and the count in ip), the pointer is built in two steps (base + c, then the
 * row offset) and the inner loop is guarded by an explicit `if (count != 0)`,
 * which is what makes agbcc rotate the outer loop into the `i + 1` /
 * `i <= 1` shape the ROM uses.
 *
 * The remaining difference is the position of the literal-pool load of 0xFFF
 * inside the inner loop's pre-header (and the r6/r7 assignment of the loop
 * counter and of the mask that follows from it).  See README.md.
 *
 * Target bytes:
 *   f0b54f464646c0b4804607981206120e91461b060006000e84460906c911090cdb0d40
 *   46c268d218407d4843400015184946ff2902d14346db7f99460020461c604600280d
 *   d00d4f49460c032b1c62461988381c0840204318800233013a002af6d14346587d40002
 *   d18301c0128e6dd18bc9846a146f0bc01bc0047ff0f0000
 */

#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0c];
    u16 *base;
    u8 unknown_10[0x05];
    u8 field_15;
    u8 unknown_16[0x09];
    u8 tag;
} State0802ACD4;

void func_0802ACD4(State0802ACD4 *state, s8 a, u8 b, u8 c, u8 count)
{
    s32 i;
    u16 row = a * 2;
    u16 *q = state->base + c;
    u16 *p = q + row * state->field_15;

    if (b == 0xFF) {
        b = state->tag;
    }

    for (i = 0; i < 2; i++) {
        if (count != 0) {
            u32 t = b << 12;
            u16 *w = p;
            u32 j = count;

            while (j != 0) {
                *w = (*w & 0xFFF) | t;
                w++;
                j--;
            }
        }
        p += state->field_15;
    }
}
