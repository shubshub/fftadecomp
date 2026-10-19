/* 0x0802B108 - 90 bytes (the index calls it 14: it actually runs to the
 * interworking return at 0x0802B160, and 0x0802B162 is the 4-byte alignment
 * pad) - MATCH.
 *
 * Walks a state block twice over: field_16*2 columns of field_15 entries,
 * deinterleaving a packed u16 source into strided u16 rows.  The source is
 * read straight through - offset simply counts up once per output slot - while
 * the destination starts each column at column * stride.
 *
 * Target bytes:
 *   f0b5031c0026987d0021002822d0987f48430004070c002201318c46587d824211d2
 *   9d68dc68b918490049197000001900880880701c0004060c501c0004020c597d8a42
 *   efd361460804010c987d40008142dcdbf0bc01bc0047
 */

#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u16 *dest;
    u16 *source;
    u8 unknown_10[5];
    u8 rows;
    u8 columns;
    u8 unknown_17[7];
    u8 stride;
} State0802B108;

void func_0802B108(State0802B108 *state)
{
    u16 offset = 0;
    u16 column;
    u16 row;

    for (column = 0; column < state->columns * 2; column++) {
        u16 base = column * state->stride;

        for (row = 0; row < state->rows; row++) {
            state->dest[base + row] = state->source[offset];
            offset++;
        }
    }
}