/* func_08017AF4 - 0x08017AF4, 40 bytes (0x08017AF4..0x08017B1C)
 *
 * The function index truncates this one at 0x08017B0A (22 bytes), mid-branch:
 * the code plainly runs on to the interworking epilogue `pop {r4}; pop {r0};
 * bx r0` at 0x08017B16, and the next function starts at 0x08017B1C.
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   target  10b5 1c04 0609 0e0b 0612 0e12 8a21 2001 4008 2800
 *           d105 0619 1609 7d63 1c20 43ff fff7 10bc 01bc 0047
 *
 * A guard-and-forward: if bit 0 of the u16 at +0x10 is clear it hands the
 * record to func_0801799C.  Both byte parameters are zero-extended in the
 * prologue before the test - the second one is then re-narrowed as signed on
 * the path that uses it, which is why `(s8)x` rather than a plain `x` is what
 * the source has to say.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u16 flags;
    u8 unknown_12[3];
    u8 field_15;
} Struct08017AF4;

void func_0801799C(Struct08017AF4 *state, s8 x, u8 a, u8 b);

void func_08017AF4(Struct08017AF4 *state, u8 x, u8 a) {
    if (!(state->flags & 1))
        func_0801799C(state, (s8)x, a, state->field_15);
}