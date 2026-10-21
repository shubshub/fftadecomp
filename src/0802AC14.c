/* 0x0802AC14 - 138 bytes (the index span ends at 0x0802AC9E, which is the real
 * end: the body runs on to the interworking return `pop {r0}; bx r0` at
 * 0x0802AC9A, 0x0802AC9E is the alignment pad and 0x0802ACA0 starts the next
 * function) - MATCH.
 *
 * Copies `count` rows out of a strided u16 source matrix into a strided u16
 * destination matrix:
 *
 *   state->first[(base + i) * state->field_16 + offset + j]
 *       = src[i * state->field_12 + j]
 *
 * `field_16` is the destination row stride and `field_12` the source row
 * stride; the destination pointer is the word at +0x00 of the state block.
 * Both strides are read as bytes here (ldrb), so this file's view of the
 * state block declares them as u8.
 *
 * The matrix is bounded: a row index above 19 and a column index above 29 are
 * skipped, which is what the two `continue`s are for.  The row test is
 * `base + i > 19` and the column test `offset + j > 29`.
 *
 * The parameters are narrowed in the prologue, not at their use (`lsls/lsrs
 * #24`), so offset, base and count are u8; the fifth parameter arrives on the
 * stack at [sp, #0x20].  Both loop counters are u16: their increments are
 * truncated with `lsls #16 / lsrs #16`.
 *
 * `dst` and `col` are u16, so the two stride products are truncated to sixteen
 * bits on their own; the destination index is then built as `dst + offset + j`,
 * where `dst + offset` is loop invariant and gets hoisted into the inner
 * loop's preheader.
 *
 * There is no literal pool; every constant is immediate.
 *
 * Target bytes:
 *   f0b557464e464546e0b4041c894608981206160e1b061b0e9a460006000e8046
 *   002242452ad250468118404600048446571c13291edca07d48430004030ca17c
 *   101c48430004050c00228a4212d29b19b0181d2808dc9918206849000918a818
 *   4000484400880880501c0004020ca07c8242edd33804020c6045d4d338bc9846
 *   a146aa46f0bc01bc0047
 */

#include "ffta.h"

typedef struct {
    u16 *first;
    u8 unknown_04[0x0E];
    u8 field_12;
    u8 unknown_13[3];
    u8 field_16;
} State0802AC14;

void func_0802AC14(State0802AC14 *state, u16 *src, u8 offset, u8 base, u8 count)
{
    u16 i;

    for (i = 0; i < count; i++) {
        u16 dst;
        u16 col;
        u16 j;

        if (base + i > 19)
            continue;

        dst = state->field_16 * (base + i);
        col = i * state->field_12;

        for (j = 0; j < state->field_12; j++) {
            if (offset + j > 29)
                continue;

            state->first[dst + offset + j] = src[col + j];
        }
    }
}
