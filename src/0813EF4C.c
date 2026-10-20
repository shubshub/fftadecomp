/* func_0813EF4C - 0x0813EF4C..0x0813EFDA, 142 bytes
 *
 * MATCHED byte-for-byte with: agbcc -mthumb-interwork -O2
 *   70b556464d46444670b4041c8a46151c1e1c079880460899099a91462d042d0c3604360c
 *   43461b041b0c98460906090e48460006000e814601202070201c00f025f9c3f639fc00
 *   04001452460423d15e03f0d8fc52461188091861805088a080e582a6824346638320
 *   1c4946fff7cafb0221605e0002a0600422a05e0002e06038bc9846a146aa4670bc01bc0047
 *
 * Places a unit on the map.  `state->field_02/field_04` are copied from the
 * first two words of `pos` (the first one offset by a scaled random value),
 * `field_08`/`field_0c` are those two coordinates shifted up eight bits, and
 * `field_14`/`field_16`/`field_1a` take the three u16 arguments verbatim.
 * `func_0813E750` then finishes the record from `arg7`.
 *
 * The store order follows the instructions, not the argument order: the
 * u16 pair lands at +0x16 before +0x14.  `arg3` is the +0x16 one.
 *
 * The s16 read of `pos[2]` needs the cast: `pos` is `u16 *`, so the same
 * access spelled `pos[2]` would load with `ldrh`.  It reaches the load as
 * `mov r2, sl / movs r3, #4 / ldrsh r1, [r2, r3]`.
 */

#include "ffta.h"

typedef struct {
    u8  unknown_00;
    u8  unknown_01;
    s16 field_02;
    s16 field_04;
    u8  unknown_06[2];
    s32 field_08;
    s32 field_0c;
    u8  unknown_10[4];
    u16 field_14;
    u16 field_16;
    u8  unknown_18;
    u8  unknown_19;
    u16 field_1a;
} State0813EF4C;

s32 func_0813F1D8(State0813EF4C *state, u8 mode);
u32 func_08002804(void);
s32 func_08142950(s32 value, s32 divisor);
void func_0813E750(State0813EF4C *state, u8 mode);

void func_0813EF4C(State0813EF4C *state, u16 *pos, u16 arg3, u16 arg4,
                   u16 arg5, u8 arg6, u8 arg7)
{
    state->unknown_00 = 1;
    func_0813F1D8(state, arg6);
    state->field_02 = pos[0] + func_08142950((s16)func_08002804(), ((s16 *)pos)[2]);
    state->field_04 = pos[1];
    state->field_16 = arg3;
    state->field_14 = arg4;
    state->field_1a = arg5;
    func_0813E750(state, arg7);
    state->field_08 = state->field_02 << 8;
    state->field_0c = state->field_04 << 8;
}
