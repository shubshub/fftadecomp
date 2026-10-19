/* func_08017E28 - 0x08017E28, 86 bytes (0x08017E28 .. 0x08017E7E)
 *
 *   30b5 051c 6868 1a21 405e 0028 03d0 297c 0420 0843 02e0
 *   297c fb20 0840 2874 6868 fff782fe 6968 1a22 8c5e 0004
 *   000c 2418 013c 081c fff7c4fe 0004 0014 8442 03d1 297c
 *   f720 0840 02e0 297c 0820 0843 2874 30bc 01bc 0047
 *
 * Two bits of the +0x10 byte of the outer record are decided from the +0x1A
 * halfword of the unit reached through +0x04:
 *
 *   0x04 is set when that halfword is non-zero and cleared when it is zero,
 *   then 0x08 is cleared when the halfword plus func_08017B50(unit) minus one
 *   equals func_08017BE8(unit), and set when it does not.
 *
 * There are no stack slots - r4 and r5 are live registers only - and the
 * epilogue is the Thumb interworking `pop {r4, r5}; pop {r0}; bx r0`.
 */

#include "ffta.h"

typedef struct {
    u8  unknown_00[0x18];
    u16 field_18;
    s16 field_1A;
} Unit08017E28;

typedef struct {
    u8           unknown_00[4];
    Unit08017E28 *field_04;
    u8           unknown_08[8];
    u8           field_10;
} State08017E28;

u16 func_08017B50(Unit08017E28 *unit);
s16 func_08017BE8(Unit08017E28 *unit);

void func_08017E28(State08017E28 *state) {
    if (state->field_04->field_1A != 0) {
        state->field_10 |= 4;
    } else {
        state->field_10 &= 0xFB;
    }

    if (state->field_04->field_1A + func_08017B50(state->field_04) - 1 ==
        func_08017BE8(state->field_04)) {
        state->field_10 &= 0xF7;
    } else {
        state->field_10 |= 8;
    }
}
