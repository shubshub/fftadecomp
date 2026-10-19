/* func_080C17C8 - 0x080C17C8, 268 bytes of code + a 76-byte literal pool
 *
 * The copy step for the state object at 0x020101F8: it packs four nibbles out
 * of the raw bytes at +0x54B0.. into the halfword-packed fields at +0x54D0,
 * copies four halfwords, and then invokes the callback the pointer word at
 * 0x0836D4BC names.
 *
 * Three shape facts the instructions give, all of which the compiler will not
 * invent on its own:
 *
 *  - The call is INDIRECT.  r3 holds the target and `bl` goes to agbcc's
 *    runtime helper `_call_via_r3` (the `bx r3` at 0x08142250), so only r0, r1
 *    and r2 are arguments - three of them, not four.  Declaring it as a direct
 *    four-argument call puts the constant 4 in r2 before r3 is set, and the
 *    whole tail shifts: 0x54DC then folds onto 0x54C2 instead of getting its
 *    own pool entry, 0x54DE off 0x54DC instead of off 0x54C2, and 0x54CC comes
 *    out of the pool instead of off 0x54DC.  Six instructions and two pool
 *    words are wrong that way.
 *
 *  - The base pointer stays in a local, one pool entry per distinct field
 *    offset, in first-use order.  0x54D1, 0x54D4, 0x54D8, 0x54DA, 0x54CC and
 *    0x54E4 have no pool entry at all: agbcc reaches them as a delta off a
 *    neighbouring offset already in a register, which is exactly what
 *    `adds r2, #0x1e`, `adds r2, #0x23`, `subs r2, #6` and `subs r3, #0x10`
 *    are.
 *
 *  - r5 = 0xF and r8 = &state->mode are live across the call, so both are
 *    callee-saved: r5 in the {r4,r5,r6,lr} prologue, r8 in the extra slot that
 *    `mov r6, r8 / push {r6}` opens and `pop {r3} / mov r8, r3` closes.
 */

#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x54B0];
    u8 field_54B0;
    u8 field_54B1;
    u8 field_54B2;
    u8 field_54B3;
    u8 field_54B4;
    u8 field_54B5;
    u8 unknown_54B6[4];
    u8 field_54BA;
    u8 field_54BB;
    u8 unknown_54BC[2];
    u16 field_54BE;
    u16 field_54C0;
    u16 field_54C2;
    u16 field_54C4;
    u8 unknown_54C6[6];
    u8 values[4];
    u8 mode : 4;
    u8 next : 4;
    u8 unknown_54D1_lo : 4;
    u8 unknown_54D1_hi : 4;
    u8 unknown_54D2_lo : 4;
    u8 unknown_54D2_hi : 4;
    u8 unknown_54D3_lo : 4;
    u8 unknown_54D3_hi : 4;
    u8 unknown_54D4_lo : 4;
    u8 unknown_54D4_hi : 4;
    u8 unknown_54D5[3];
    u16 field_54D8;
    u16 field_54DA;
    u16 field_54DC;
    u16 field_54DE;
    u8 unknown_54E0[4];
    u32 unknown_54E4;
    u8 field_54E8;
    u8 unknown_54E9[3];
} State080C17C8;

void func_080C17C8(void)
{
    State080C17C8 *state = (State080C17C8 *)0x020101F8;

    state->mode = state->field_54BA;
    state->unknown_54D2_lo = state->field_54B2;
    state->unknown_54D2_hi = state->field_54B3;
    state->unknown_54D1_lo = state->field_54B4;
    state->unknown_54D1_hi = state->field_54B5;
    state->field_54D8 = state->field_54BE;
    state->field_54DA = state->field_54C0;
    state->unknown_54D4_lo = state->field_54BB;
    state->unknown_54D3_lo = state->field_54B0;
    state->unknown_54D3_hi = state->field_54B1;
    state->field_54DC = state->field_54C2;
    state->field_54DE = state->field_54C4;
    ((void (*)(void *, void *, s32))*(u32 *)0x0836D4BC)
        (state->values, &state->unknown_54E4, 4);
    state->next = state->field_54E8;
}