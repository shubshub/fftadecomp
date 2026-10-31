#include "ffta.h"

/* Complete [0x0805C340, 0x0805C3D2): 146 bytes, 70 instructions.
 * Target bytes:
 * 70b54e46454660b483b08046101c1e1c0906090e0006000e3606360e4246527d
 * 91464d464d436d042d0c4246917d0131e6f0eefa4c46444364004046808b2418
 * 2404240c022000900196002002904046291c221c4b46cef7e5fb02352d042d0c
 * 04342404240c41464b7d981e0006000e0090c87f0190012002904046291c221c
 * cef7d0fb03b018bc9846a14670bc01bc0047
 */

typedef struct {
    u8 unknown_00[0x0C];
    u16 *base;
    u8 unknown_10[5];
    u8 field_15;
    u8 field_16;
    u8 unknown_17[5];
    u16 field_1C;
    u8 unknown_1E;
    u8 field_1F;
} State0805C340;

extern s32 func_08142950(s32, s32);
extern void func_0802AB64(State0805C340 *, u16, u16, u8, u8, u16, u8);

void func_0805C340(State0805C340 *state, u8 index, u8 selection, u8 tag)
{
    u8 width = state->field_15;
    u16 first = width * index * 2;
    u32 remainder = (u32)func_08142950(selection, state->field_16 + 1);
    u16 value = width * remainder * 2 + state->field_1C;

    func_0802AB64(state, first, value, width, 2, tag, 0);
    first += 2;
    value += 4;
    func_0802AB64(state, first, value, state->field_15,
                  (u8)(state->field_15 - 2), state->field_1F, 1);
}
