/* func_08009FD0 - 0x08009FD0, 40 bytes (28 code + 12 literal pool)
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   target  00b5 0648 064a 8118 0988 023a 8018 0180 0448 0121 bff0c6fa 01bc 0047
 *   pool 0x08009FEC: 0x02000000
 *   pool 0x08009FF0: 0x00002194
 *   pool 0x08009FF4: 0x0000021F
 *
 * symbols/functions.txt records 22 bytes here, which cuts the `bl` in half;
 * the body runs to the interworking return at 0x08009FEA and the three literal
 * pool words follow it, so the ELF symbol is 40 bytes.
 *
 * Publishes the head of a queue of u16 values that lives in the game's main
 * state block: the halfword at +0x2194 is copied to the halfword at +0x2192
 * and the "changed" flag bit 0x21F is set.  The queue itself is filled by the
 * script opcode at 0x08122EC0, which appends to +0x2194 and bumps the count
 * byte at +0x219C; 0x08121F38 drops the oldest entry by shifting the queue
 * down and then calls this function to publish the new head.
 */

#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2192];
    u16 current;
    u16 queued[4];
    u8 count;
} State;

extern u8 g_state_02000000[];

void func_080C9574(u16 bitIndex, u16 enabled);

void func_08009FD0(void)
{
    State *state = (State *)g_state_02000000;
    u16 value = state->queued[0];

    state->current = value;
    func_080C9574(0x21F, 1);
}
