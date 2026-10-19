/* func_080C1654 - 0x080C1654, 142 bytes of code + a 30-byte literal pool
 *
 * Sets five fields of the state object at 0x020101F8 and then pushes one entry
 * into its four-entry ring.  The offsets 0x54CC..0x54DC are the ones the
 * instructions give; the seven pool entries are the base address and six
 * *separate* per-field offsets, so the base has to stay in a local pointer -
 * folding the offsets into absolute addresses gives one pool entry per access
 * and loses the register roles (the failure mode in Parked/08009888).
 *
 * Register allocation is what fixes most of the frame:
 *   r8/r9/r10 (r5/r6/r7) hold the base, the 0x54D2 byte and the 0x54D2 pointer
 *   for three values that are live at once, which is why all three are pushed
 *   on top of the {r4-r7,lr} prologue.
 *
 * Two type facts the instructions give directly:
 *   - `a` and `e` are read as u8 (lsls #24 / lsrs #24 on each), and land in
 *     4-bit fields, so they are masked with 0xF;
 *   - `b` only ever reaches the high nibble, and agbcc spells that insert as
 *     (b << 24) >> 20 rather than masking first - a `u8 b` reproduces it.
 *
 * The argument at [sp, #0x20] is the fifth parameter: the frame is 32 bytes
 * and this toolchain places the fifth parameter at frame + 0, which
 * func_08017514 (8-byte frame, fifth parameter at [sp, #8]) also shows.
 *
 *   target  f0b5 5746 4e46 4546 e0b4 089c a046 0006 000e 0906 4546 2d06
 *           2d0e a846 1c4f b946 1c4c 4c44 a446 0f26 3040 2578 aa46 1025
 *           6d42 2c1c 5746 3c40 0443 090d 3440 0c43 6046 0470 1448 4844
 *           0280 1448 4844 0380 1349 4944 4446 3440 0878 0540 2543 0d70
 *           104b 4b44 1a78 1106 080f 0130 0001 1640 0643 1e70 090f 0c4d
 *           a944 4944 0320 0870 38bc 9846 a146 aa46 f0bc 01bc 0047
 *           0000 f801 0102 d254 0000 d854 0000 da54 0000 d454 0000
 *           d054 0000 cc54 0000
 */

#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x54CC];
    u8 values[4];
    u8 mode : 4;
    u8 next : 4;
    u8 unknown_54D1;
    u8 unknown_54D2_lo : 4;
    u8 unknown_54D2_hi : 4;
    u8 unknown_54D3;
    u8 unknown_54D4_lo : 4;
    u8 unknown_54D4_hi : 4;
    u8 unknown_54D5[3];
    u16 field_54D8;
    u16 field_54DA;
} State080C1654;

void func_080C1654(u8 a, u8 b, u16 c, u16 d, u8 e) {
    State080C1654 *state = (State080C1654 *)0x020101F8;

    state->unknown_54D2_lo = a;
    state->unknown_54D2_hi = b;
    state->field_54D8 = c;
    state->field_54DA = d;
    state->unknown_54D4_lo = e;
    state->values[state->next++] = 3;
}